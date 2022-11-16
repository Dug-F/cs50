import re
import sys


def main():
    print(count(input("Text: ")))


def count(s):
    # match "um" with either a non-numeric char or start of phrase before and either a non-numeric char or start of phrase after
    if matches := re.findall(r'(?:[^a-z0-9]|^)um(?:[^a-z0-9]|$)', s, re.IGNORECASE):
        return len(matches)
    return 0


if __name__ == "__main__":
    main()