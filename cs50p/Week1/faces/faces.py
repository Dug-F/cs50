def main():
    # get input from user
    phrase = input("Enter your phrase: ")

    # print converted phrase
    print(convert(phrase))


def convert(phrase):
    # replace text with emojis
    phrase = phrase.replace(":)", "🙂")
    phrase = phrase.replace(":(", "🙁")
    return phrase


if __name__ == "__main__":
    main()