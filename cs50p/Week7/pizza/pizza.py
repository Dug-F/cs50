from tabulate import tabulate
import sys
import csv

def main():
    # validate command line parameter
    if len(sys.argv) < 2:
        sys.exit("Too few command-line arguments")
    elif len(sys.argv) > 2:
        sys.exit("Too many command-line arguments")
    if not sys.argv[1].endswith(".csv"):
        sys.exit("Not a CSV file")

    table = []
    # read file and accumulate into list
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        for row in reader:
            table.append(row)

    # print tabulated list
    print(tabulate(table, headers="firstrow", tablefmt="grid"))

if __name__ == "__main__":
    main()