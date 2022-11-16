from emoji import emojize

def main():
    raw_string = input("Input: ").strip()
    print(f"Output: {emojize(raw_string, language='alias')}")

if __name__ == "__main__":
    main()