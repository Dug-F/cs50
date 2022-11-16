def main():
    answer = input("What is the answer to Great Question of Life, the Universe and Everything? ")
    if is_answer(answer):
        print("Yes")
    else:
        print("No")


def is_answer(answer):
    return answer.lower().strip() in ["42", "forty-two", "forty two"]


if __name__ == "__main__":
    main()