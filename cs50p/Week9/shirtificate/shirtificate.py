from fpdf import FPDF
from PIL import Image

H_MARGIN = 10

def main():
    name = input("Name: ")

    pdf = FPDF(orientation="portrait", format="A4", unit="mm")
    pdf.add_page()

    pdf.set_font("helvetica", "B", 50)
    pdf.cell(0, 60, "CS50 Shirtificate", new_x="LMARGIN", new_y="NEXT", align="C")

    image_percent_width = 1
    image_x = pdf.epw * (1 - image_percent_width) / 2 + H_MARGIN

    pdf.image("shirtificate.png", w=pdf.epw * image_percent_width, x = image_x, y=60)

    pdf.set_font_size(40)
    pdf.set_text_color(255, 255, 255)
    pdf.set_y(120)
    pdf.multi_cell(w=200, h=None, txt=f"{name}\ntook CS50", new_x="LMARGIN", new_y="NEXT", align="C")

    # image_percent_width = 0.3
    # image_x = pdf.epw * (1 - image_percent_width) / 2 + H_MARGIN
    # pdf.image("cs50p.jpg", w=pdf.epw * image_percent_width, x = image_x + 4, y=160)

    pdf.output("shirtificate.pdf")


if __name__ == "__main__":
    main()