def main():
    # get input from user
    phrase = input("Enter your phrase: ")

    # print slowed down phrase
    print(f"{phrase.replace(' ', '...')}")


if __name__ == "__main__":
    main()