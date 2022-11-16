def main():
    name = input("Input: ")
    print(f"Output: {shorten(name)}")


def shorten(name):
    # remove all vowels from string
    return "".join([replace(char) for char in name])


def replace(char):
    # remove char if vowel
    return "" if char.lower() in ['a', 'e', 'i', 'o', 'u'] else char


if __name__ == "__main__":
    main()