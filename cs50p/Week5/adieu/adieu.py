def main():
    names = []
    while True:
        # get input names from user
        try:
            name = input("Name: ")
            names.append(name)
        except EOFError:
            break

    # print formatted list of names
    print(f"Adieu, adieu, to {format_names(names)}")


def format_names(names):
    # format list of names
    name_count = len(names)
    if name_count == 1:
        return names[0]
    if name_count == 2:
        return ' and '.join(names)

    return f"{', '.join(names[:-1])}, and {names[-1]}"


if __name__ == "__main__":
    main()