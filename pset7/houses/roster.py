from cs50 import SQL
import csv
from sys import argv, exit


def main():

    # Veryfing if the user typed only two arguments
    if len(argv) != 2:
        print("type only two arguments in the command line!")
        exit(1)

    house = argv[1]

    # Open that file for SQLite
    db = SQL("sqlite:///students.db")

    roster = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)

    for i in roster:
        if i['middle'] == None:
            print(f'{i["first"]} {i["last"]}, born {i["birth"]}')
        else:
            print(f'{i["first"]} {i["middle"]} {i["last"]}, born  {i["birth"]}')


main()