import sys

def main():
    # validate command line parameter
    if len(sys.argv) < 2:
        sys.exit("Too few command-line arguments")
    elif len(sys.argv) > 2:
        sys.exit("Too many command-line arguments")
    if not sys.argv[1].endswith(".py"):
        sys.exit("Not a Python file")

    # open file and count lines
    count = 0
    try:
        with open(sys.argv[1], "r") as file:
            for line in file:
                line = line.lstrip()
                if line == "" or line.startswith('#'):
                    continue
                count += 1
    except FileNotFoundError:
        sys.exit(f"File does not exist")

    # print line count
    print(count)


if __name__ == "__main__":
    main()