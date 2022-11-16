#include "helpers.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// function prototypes
void calc_pixel_values(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE temp_image[height][width], int h, int w);
bool in_grid(int position, int min, int max);
BYTE max_byte(int pixel);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for greyscale, each of the red, green and blue bytes are set to the average of the 3 for each pixel
    BYTE greyscale_pixel;
    for (int w = 0; w < width; w++)
    {
        for (int h = 0; h < height; h++)
        {
            greyscale_pixel = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtBlue = greyscale_pixel;
            image[h][w].rgbtGreen = greyscale_pixel;
            image[h][w].rgbtRed = greyscale_pixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // formula for sepia is:
    //  sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    //  sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    //  sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

    int sepia_pixel;
    for (int w = 0; w < width; w++)
    {
        for (int h = 0; h < height; h++)
        {
            BYTE sepiaRed = max_byte(round(0.393 * image[h][w].rgbtRed + 0.769 * image[h][w].rgbtGreen + 0.189 * image[h][w].rgbtBlue));
            BYTE sepiaGreen = max_byte(round(0.349 * image[h][w].rgbtRed + 0.686 * image[h][w].rgbtGreen + 0.168 * image[h][w].rgbtBlue));
            BYTE sepiaBlue = max_byte(round(0.272 * image[h][w].rgbtRed + 0.534 * image[h][w].rgbtGreen + 0.131 * image[h][w].rgbtBlue));

            image[h][w].rgbtBlue = sepiaBlue;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        // temp copy current row to allow bytes to be moved around
        RGBTRIPLE temp_row[width];
        for (int i = 0; i < width; i++)
        {
            temp_row[i] = image[h][i];
        }

        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = temp_row[(width - 1) - w].rgbtBlue;
            image[h][w].rgbtGreen = temp_row[(width - 1) - w].rgbtGreen;
            image[h][w].rgbtRed = temp_row[(width - 1) - w].rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // get a temp copy of the image
    RGBTRIPLE temp_image[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp_image[h][w] = image[h][w];
        }
    }

    // update each colour byte for each pixel to be the average of the itself and all pixels within 1 pixel distance (including diagonals)

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            calc_pixel_values(height, width, image, temp_image, h, w);
        }
    }

    return;
}

void calc_pixel_values(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE temp_image[height][width], int h, int w)
{
    int count = 0, blue_total = 0, green_total = 0, red_total = 0;

    // iterate averaging over 3 x 3 grid
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (in_grid(h + i, 0, height - 1) && in_grid(w + j, 0, width - 1))
            {
                count ++;
                blue_total += temp_image[h + i][w + j].rgbtBlue;
                green_total += temp_image[h + i][w + j].rgbtGreen;
                red_total += temp_image[h + i][w + j].rgbtRed;
            }
        }
    }
    image[h][w].rgbtBlue = max_byte(round(blue_total / (float) count));
    image[h][w].rgbtGreen = max_byte(round(green_total / (float) count));
    image[h][w].rgbtRed = max_byte(round(red_total / (float) count));
}

bool in_grid(int position, int min, int max)
{
    if (position < min || position > max)
    {
        return false;
    }
    return true;
}

BYTE max_byte(int pixel)
{
    if (pixel > 255)
    {
        return (BYTE) 255;
    }
    return (BYTE) pixel;
}