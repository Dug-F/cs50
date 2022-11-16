import re
import sys

def main():
    print(validate(input("IPv4 Address: ")))


def validate(ip):
    # match 4 ip addresses
    if matches := re.search(r"^([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})$", ip):
        # invalid if any node out of range
        for i in range(1, 5):
            if not (255 >= int(matches.group(i)) >= 0):
                return False
        return True
    return False


if __name__ == "__main__":
    main()