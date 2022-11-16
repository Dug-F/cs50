def main():
    # get expression from user
    expression = input("Expression: ")
    print(f"{calculate(expression):.1f}")


def calculate(expression):
    # split expression to get components
    op1, operation, op2 = expression.split(" ")
    op1, op2 = int(op1), int(op2)

    # perform calculation, depending on operation
    match operation:
        case "+":
            return op1 + op2
        case "-":
            return op1 - op2
        case "*":
            return op1 * op2
        case "/":
            return float(op1) / op2

    return 0

if __name__ == "__main__":
    main()