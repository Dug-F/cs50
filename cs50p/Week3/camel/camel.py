def main():
    name = input("camelCase: ")
    print(to_camel_string(name))


def to_camel_string(name):
    # convert all characters to snake case
    return "".join([to_snake_char(char) for char in name])


def to_snake_char(char):
    # convert upper case to _ + lower case
    return f"_{char.lower()}" if char.isupper() else char


if __name__ == "__main__":
    main()