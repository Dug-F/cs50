import re
import sys


def main():
    print(parse(input("HTML: ")))


def parse(s):

    # parse embedded youtube href
    if matches := re.search(r'http.*/embed/([a-z0-9]*)"', s, re.IGNORECASE):
    # alternate match string
    # if matches := re.search(r'https?://(?:www.)?youtube\.com/embed/([a-z0-9]*)"', s, re.IGNORECASE):
        # return composed short youtube link ref
        return f"https://youtu.be/{matches.group(1)}"
    else:
        return None


if __name__ == "__main__":
    main()