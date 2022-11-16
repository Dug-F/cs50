from pyfiglet import Figlet
import random
import sys

def main():
    # print text in figlet fonts

    # instantiate figlet object
    figlet = Figlet()

    # if no font has been set, command line parameters were invalid
    if (font := get_font(figlet.getFonts())) is None:
        sys.exit("Invalid usage")

    # get input from user
    text = input("Input: ")
    # set figlet font
    figlet.setFont(font=font)
    # print figlet output
    print(f"Output:\n\n{figlet.renderText(text)}")


def get_font(available_fonts):
    # initialise variables
    param_count = len(sys.argv)

    # validate command line parameters
    if param_count == 1:
        return random.choice(available_fonts)

    if param_count == 3:
        if sys.argv[1] in ["-f", "-font"] and sys.argv[2] in available_fonts:
            return sys.argv[2]

    # command line parameters invalid
    return None

if __name__ == "__main__":
    main()