items = {
    "baja taco": 4.00,
    "burrito": 7.50,
    "bowl": 8.50,
    "nachos": 11.00,
    "quesadilla": 8.50,
    "super burrito": 8.50,
    "super quesadilla": 9.50,
    "taco": 3.00,
    "tortilla salad": 8.00
}

def main():
    total = 0
    while True:
        try:
            # get user input
            order = input("Item: ")
            if (item_cost := items.get(order.lower())) is None:
                continue
            total += item_cost
            print(f"Total: ${total:.2f}")
        except EOFError:
            print()
            break


if __name__ == "__main__":
    main()