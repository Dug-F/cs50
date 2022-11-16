def main():
    items = {}
    while True:
        try:
            # get user input
            item = input()
            if item in items:
                # increment item count if already in dict
                items[item] += 1
            else:
                # otherwise add item and initialise to 1
                items[item] = 1
        except EOFError:
            break

    # print out items
    for key, value in sorted(items.items()):
        print(f"{value} {key.upper()}")


if __name__ == "__main__":
    main()