import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py csv_file.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    database = {}
    with open(sys.argv[1], "r") as db_file:
        csv_reader = csv.DictReader(db_file)
        db_strs = csv_reader.fieldnames[1:]
        for row in csv_reader:
            database[row['name']] = {key: row[key] for key in db_strs}

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as sequence_file:
        sequence = sequence_file.readlines()[0]

    # Find longest match of each STR in DNA sequence
    seq_str_counts = {}
    for seq_str in db_strs:
        seq_str_counts[seq_str] = str(longest_match(sequence, seq_str))

    # Check database for matching profiles
    for name, db_str_counts in database.items():
        if seq_str_counts == db_str_counts:
            print(name)
            return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()
