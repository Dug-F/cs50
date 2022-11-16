def main():
    # get input from user
    m = int(input("m: "))

    # print calculated energy
    print(f"E: {calc_energy(m)}")


def calc_energy(m):
    c = 300000000
    return m * pow(c, 2)



if __name__ == "__main__":
    main()