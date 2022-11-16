# TODO

# Calculate reading age of input text

def main():
    text = input("Test: ")

    letters, words, sentences = 0, 0, 0

    # calculate letter, word and sentence counts
    for char in text:
        if char.isalpha():
            letters += 1
        if char == " ":
            words += 1
        if char in [".", "!", "?"]:
            sentences += 1

    # increment the word count if any letters found, since the last word is not followed by a space
    if letters > 0:
        words += 1

    # calculate reading index
    l = letters * 100 / words
    s = sentences * 100 / words
    index = round(0.0588 * l - 0.296 * s - 15.8)

    # print reading index
    if index >= 16:
        print("Grade 16+")
    elif index <= 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()