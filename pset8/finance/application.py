import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    stocks = db.execute("SELECT * FROM wallet WHERE users_id = :user_id",
                        user_id=session["user_id"])

    user = db.execute("SELECT * FROM users WHERE id = :user_id",
                        user_id=session["user_id"])

    # Checking the updated stock prices
    total_cash = 0

    for i in range(len(stocks)):
        stock = lookup(stocks[i]["symbol"])

        stocks[i]["price"] = round((stock["price"]), 2)
        stocks[i]["total"] = round((stock["price"] * float(stocks[i]["shares"])), 2)

        total_cash += stocks[i]["total"]

    total_cash += float(user[0]["cash"])


    return render_template("index.html", stocks=stocks, cash=usd(user[0]["cash"]), total_cash=usd(total_cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        action = 'buy'

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("missing symbol", 400)

        # Ensure shares were submitted
        if not request.form.get("shares"):
            return apology("missing shares", 400)

        # Query database for username
        quote = lookup(request.form.get("symbol"))

        if not quote:
            return apology("invalid symbol", 400)

        # Query database for user's cash
        user = db.execute("SELECT * FROM users WHERE id = :id",
                          id=session["user_id"])

        # Saving in shares for use
        shares = int(request.form.get("shares"))

        # Calculating the total for this transation
        total_local = quote["price"] * float(shares)
        cash = user[0]["cash"]

        # Checking if the user has enough cash to buy
        if  cash < total_local:
            return apology("can't afford", 400)

        # Updating the user's cash
        cash_updated = cash - total_local

        db.execute("UPDATE users SET cash = :cash_updated WHERE id = :user_id",
                    cash_updated=cash_updated, user_id=session["user_id"])

        # Insert the transation in transfer
        db.execute("INSERT INTO transfers (users_id, symbol, name, shares, price, action) VALUES (:user_id, :symbol, :name, :shares, :prices, :action)",
                    user_id=session["user_id"], symbol=quote["symbol"], name=quote["name"], shares=shares, prices=round(quote["price"], 2), action=action)


        # Query user's wallet for symbol
        rows = db.execute("SELECT * FROM wallet WHERE users_id = :user_id AND symbol = :symbol",
                            user_id=session["user_id"], symbol=quote["symbol"])

        # Insert or update in wallet
        if len(rows) == 0:
            db.execute("INSERT INTO wallet (users_id, symbol, name, shares, price, total) VALUES (:user_id, :symbol, :name, :shares, :price, :total)",
                        user_id=session["user_id"], symbol=quote["symbol"], name=quote["name"], shares=shares, price=round(quote["price"], 2), total=round(total_local, 2))
        else:
            shares = rows[0]["shares"] + shares
            db.execute("UPDATE wallet SET shares = :shares, total = :total WHERE users_id = :user_id AND symbol = :symbol",
                        shares=shares, total=round(float(rows[0]["total"])+total_local, 2), user_id=session["user_id"], symbol=quote["symbol"])

        # Query to show to user
        stocks = db.execute("SELECT * FROM wallet WHERE users_id = :user_id",
                        user_id=session["user_id"])

        user = db.execute("SELECT * FROM users WHERE id = :user_id",
                        user_id=session["user_id"])

        # Checking the updated stock prices
        total_cash = 0

        for i in range(len(stocks)):
            stock = lookup(stocks[i]["symbol"])

            stocks[i]["price"] = round((stock["price"]), 2)
            stocks[i]["total"] = round((stock["price"] * float(stocks[i]["shares"])), 2)

            total_cash += stocks[i]["total"]

        total_cash += float(user[0]["cash"])

        # Redirect user to sucess page
        return render_template("sucess.html", action="Bought!", stocks=stocks, cash=usd(user[0]["cash"]), total_cash=usd(total_cash))

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    stocks = db.execute("SELECT * FROM transfers WHERE users_id = :user_id",
                        user_id=session["user_id"])

    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def change_password():
    """Change Password"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure confirmarion was submitted
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 403)

        # Ensure password matches confirmation
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("password and confirmation must match", 403)

        # Update hash
        db.execute("UPDATE users SET hash = :hash WHERE username = :username",
                    hash=generate_password_hash(request.form.get("password")), username=session["user_id"])

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("change.html")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("missing symbol", 400)

        # Query database for username
        quote = lookup(request.form.get("symbol"))

        if not quote:
            return apology("invalid symbol", 400)

        print(quote)

        # Redirect user to home page
        return render_template("quoted.html", quote=quote)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure confirmarion was submitted
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 403)

        # Ensure password matches confirmation
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("password and confirmation must match", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Check if the username exists in the database
        if len(rows) != 0:
            return apology("username already registered", 403)

        # Insert user in the database
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                    username=request.form.get("username"), hash=generate_password_hash(request.form.get("password")))

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute("SELECT * FROM wallet WHERE users_id = :user_id", user_id=session["user_id"])

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        action = 'sell'

        # ensure quantity was submited
        if not request.form.get("shares") or int(request.form.get("shares")) < 1:
            return apology("must provide valid number of shares", 403)

        user_id = session["user_id"]
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # retrieve stock from db
        stock = db.execute("SELECT * FROM wallet WHERE users_id = :user_id AND symbol = :symbol",
                            user_id=user_id, symbol=symbol)
        if stock:
            stock = stock[0]
        else:
            return render_template("sell.html", stocks=stocks)

        # retrieve user data from db
        user = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)

        # ensure quantity to be sold is available
        if int(shares) > stock["shares"]:
            return apology("You have no enough shares avaiable", 403)

        # lookup the stock to get current price
        stock_updated = lookup(symbol)

        # calculate total price
        total_price = float(stock_updated["price"]) * float(shares)

        # modify number of shares owned or delete if < 1
        if int(shares) == stock["shares"]:
            db.execute("DELETE FROM wallet WHERE users_id = :user_id AND symbol = :symbol", user_id=user_id, symbol=symbol)
        else:
            new_quantity = int(stock["shares"]) - int(shares)
            new_total = float(new_quantity) * float(stock["price"])
            db.execute("UPDATE wallet SET shares = :shares, total = :total WHERE users_id = :user_id AND symbol = :symbol",
                        shares=new_quantity, total=new_total, user_id=user_id, symbol=symbol)

        # modify available funds
        cash_updated = float(user[0]["cash"]) + total_price
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=cash_updated, user_id=user_id)

        # commit to transfer
        db.execute("INSERT INTO transfers (users_id, symbol, name, shares, price, action) VALUES (:user_id, :symbol, :name, :shares, :price, :action)",
                    user_id=user_id, symbol=symbol, name=stock["name"], shares=shares, price=stock["price"], action=action)


        # Query to show to user
        stocks = db.execute("SELECT * FROM wallet WHERE users_id = :user_id",
                        user_id=session["user_id"])

        # Checking the updated stock prices
        total_cash = cash_updated

        for stock in stocks:
            total_cash += stock["price"] * stock["shares"]

        # Redirect user to sucess page
        return render_template("sucess.html", action="Sold!", stocks=stocks, cash=usd(cash_updated), total_cash=usd(total_cash))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
