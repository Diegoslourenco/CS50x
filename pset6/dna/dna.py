import csv
from sys import argv, exit


def main():

    if len(argv) != 3:
        print("type only two arguments in the command line!")
        exit(1)

    # Opening csv and txt
    filetxt = open_text(argv[2])

    # Counting the number of columns
    filecsv = open_csv(argv[1])
    numberColumns = len(next(filecsv))

    # Definying the count
    count = dict()
    namesOutput = dict()
    finalList = []

    # Taking the keys in the new dict
    filecsv = open_csv(argv[1])
    for row in filecsv:
        for key in row.keys():
            if key is not count and key != 'name':
                count[key] = 0

    # Counting the sequences and putting in the count
    for key in count.keys():
        count[key] = count_times(filetxt, key)

    filecsv = open_csv(argv[1])
    for row in filecsv:
        for key, value in row.items():
            if key != 'name' and count[key] == int(value):
                if row['name'] not in namesOutput:
                    namesOutput[row['name']] = 1
                else:
                    namesOutput[row['name']] += 1

    for key, value in namesOutput.items():
        if numberColumns - 1 == value:
            finalList.append(key)

    if finalList == []:
        print('No match')
    else:
        for i in range(len(finalList)):
            print(finalList[i])



# Open the csv file and return in a dictionary
def open_csv(file_path):
    return csv.DictReader(open(file_path, newline=''))

# Open the txt file, return it and close the dictionary
def open_text(file_path):
    with open(file_path, 'r') as file:
        return file.read()

# Count the times the sequence repat in the file and return the longest sequence
def count_times(file, sequence):

    longest = 0
    length = len(sequence)

    for i in range(len(file)):
        if file[i:i+length] == sequence:

            count = 1

            for j in range(i+length, len(file), length):
                if file[j:j+length] == sequence:
                    count += 1

                elif count > longest:
                    longest = count
                    break

                else:
                    break
    return longest


main()