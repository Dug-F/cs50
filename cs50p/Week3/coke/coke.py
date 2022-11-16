def main():
    amount_due = 50
    while True:
        coin = int(input("Input coin: "))
        # if valid coin entered
        if coin in [5, 10, 25]:
            # calc new amount due
            amount_due -= coin
        # print new amount due
        print(due_text(amount_due))
        # exit if sufficient payment made
        if amount_due <= 0:
            break


def due_text(amount_due):
    # compose text for amount due
    return f"Amount due: {amount_due}" if amount_due > 0 else f"Change owed: {-amount_due}"


if __name__ == "__main__":
    main()