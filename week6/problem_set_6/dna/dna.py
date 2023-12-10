import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("INVALID_INPUT")
    else:
        # Read the CSV file into memory
        csv_data = []
        with open(sys.argv[1], "r") as csvfile:
            read = csv.reader(csvfile)
            for row in read:
                csv_data.append(row)
            # print(csv_data[1][1:])
        # TODO: Read DNA sequence file into a variable
        with open(sys.argv[2], "r") as file:
            dna_sequence = file.read()
            # Extract the STR sequences from the first row of the CSV file
            str_sequences = csv_data[0][1:]
            # TODO: Find longest match of each STR in DNA sequence
            checklist = {}
            for str in str_sequences:
                match = longest_match(dna_sequence, str)
                checklist[str] = match
            # print(checklist)
            # TODO: Check database for matching profiles
            for i in range(1, len(csv_data)):
                row = csv_data[i]
                name = csv_data[i][0]
                counts = [int(count) for count in row[1:]]
                if counts == list(checklist.values()):
                    print(name)
                    sys.exit(0)
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


main()
