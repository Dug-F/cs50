import sys
import csv

def main():
    # validate command line parameter
    if len(sys.argv) < 3:
        sys.exit("Too few command-line arguments")
    elif len(sys.argv) > 3:
        sys.exit("Too many command-line arguments")

    students = []
    headers = ["first", "last", "house"]
    # read records in input file
    try:
        with open(sys.argv[1], "r") as input_file:
            reader = csv.DictReader(input_file)
            for row in reader:
                # split full name into first and last names
                last, first = row['name'].split(", ")
                # append dict for the row
                students.append({"last": last, "first": first, "house": row["house"]})
    except FileNotFoundError:
        sys.exit(f"Could not read {sys.argv[1]}")

    # write output file
    with open(sys.argv[2], "w") as output_file:
        writer = csv.DictWriter(output_file, fieldnames=headers)
        writer.writeheader()
        for student in students:
            writer.writerow({header: student[header] for header in headers})

if __name__ == "__main__":
    main()