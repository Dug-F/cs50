def main():
    while True:
        try:
            # get user input of height
            height = int(input("Height:\n"))
        except ValueError:
            continue
        if height in range(1, 9):
            break

    # print out bricks
    for i in range(1, height + 1):
        print(f"{' ' * (height - i)}{'#' * i}")


if __name__ == "__main__":
    main()
