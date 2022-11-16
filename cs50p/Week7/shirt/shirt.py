from PIL import Image, ImageOps
import sys
from os.path import splitext

def main():
    # validate command line parameter
    valid_file_types = ['.jpg', '.jpeg', '.png']
    if len(sys.argv) < 3:
        sys.exit("Too few command-line arguments")
    elif len(sys.argv) > 3:
        sys.exit("Too many command-line arguments")
    _, infile_ext = splitext(sys.argv[1])
    _, outfile_ext = splitext(sys.argv[2])
    if infile_ext != outfile_ext:
        sys.exit("Input and output have different extensions")
    if not all([infile_ext in valid_file_types, outfile_ext in valid_file_types]):
        sys.exit("Invalid input")

    # get subject image
    subject = Image.open(sys.argv[1])

    # get shirt image
    shirt = Image.open("shirt.png")

    # size/crop subject image to shirt
    subject = ImageOps.fit(subject, shirt.size)
    # paste shirt image over subject using shirt image transparency as mask
    subject.paste(shirt, shirt)
    # save merged image in output file
    subject.save(sys.argv[2])


if __name__ == "__main__":
    main()