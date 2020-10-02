from cs50 import SQL
import csv
from sys import argv, exit


def main():

    # Veryfing if the user typed only two arguments
    if len(argv) != 2:
        print("type only two arguments in the command line!")
        exit(1)

    # Open that file for SQLite
    db = SQL("sqlite:///students.db")

    # Open the csv file
    with open(argv[1]) as file:

        # Create a DicReader
        reader = list(csv.DictReader(file))

        for i in reader:
            i['name'] = i['name'].split(" ")
            if (len(i['name']) == 2):
                i['name'].append(None)
                i['name'][1], i['name'][2] = i['name'][2], i['name'][1]

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       i['name'][0], i['name'][1], i['name'][2], i['house'], i['birth'])


main()