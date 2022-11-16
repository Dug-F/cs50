def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


def is_valid(s):
    # validate input plate

    # must be min 2 characters (letters or numbers) and max 6 characters
    if not(6 >= len(s) >= 2):
        return False

    number_found = False
    for i, char in enumerate(s):
        # no periods, spaces or punctuation
        if not char.isalnum():
            return False

        # must start with 2 letters
        if i < 2 and not char.isalpha():
            return False

        if number_found:
            # numbers must be at the end
            if char.isalpha():
                return False
        else:
            # first number cannot be 0
            if char == "0":
                return False

        if char.isnumeric():
            number_found = True

    return True


main()