def main():
    name = input("Input: ")
    print(f"Output: {remove_vowel_string(name)}")


def remove_vowel_string(name):
    # remove all vowels from string
    return "".join([remove_vowel_char(char) for char in name])


def remove_vowel_char(char):
    # remove char if vowel
    return "" if char.lower() in ['a', 'e', 'i', 'o', 'u'] else char


if __name__ == "__main__":
    main()