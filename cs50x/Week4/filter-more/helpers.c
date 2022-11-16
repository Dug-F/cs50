#include "helpers.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// function prototypes
void computeBlurPixels(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE tempImage[height][width], int h, int w);
void computeEdgePixels(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE tempImage[height][width], \
                       int h, int w, int gX[3][3], int gY[3][3]);
void copyImageArray(int height, int width, RGBTRIPLE copyFrom[height][width], RGBTRIPLE copyTo[height][width]);
bool inGrid(int position, int min, int max);
BYTE maxByte(int pixel);

typedef struct
{
    int blue;
    int green;
    int red;
}
PIXELINT;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for greyscale, each of the red, green and blue bytes are set to the average of the 3 for each pixel
    BYTE greyscalePixel;
    for (int w = 0; w < width; w++)
    {
        for (int h = 0; h < height; h++)
        {
            greyscalePixel = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtBlue = greyscalePixel;
            image[h][w].rgbtGreen = greyscalePixel;
            image[h][w].rgbtRed = greyscalePixel;
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
        RGBTRIPLE tempRow[width];
        for (int i = 0; i < width; i++)
        {
            tempRow[i] = image[h][i];
        }

        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = tempRow[(width - 1) - w].rgbtBlue;
            image[h][w].rgbtGreen = tempRow[(width - 1) - w].rgbtGreen;
            image[h][w].rgbtRed = tempRow[(width - 1) - w].rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // get a temp copy of the image
    RGBTRIPLE tempImage[height][width];
    copyImageArray(height, width, image, tempImage);

    // update each colour byte for each pixel to be the average of the itself and all pixels within 1 pixel distance (including diagonals)

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            computeBlurPixels(height, width, image, tempImage, h, w);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // get a temp copy of the image
    RGBTRIPLE tempImage[height][width];
    copyImageArray(height, width, image, tempImage);

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            computeEdgePixels(height, width, image, tempImage, h, w, gX, gY);
        }
    }

    return;
}

void computeBlurPixels(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE tempImage[height][width], int h, int w)
{
    int count = 0, blueTotal = 0, greenTotal = 0, redTotal = 0;

    // iterate averaging over 3 x 3 grid
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (inGrid(h + i, 0, height - 1) && inGrid(w + j, 0, width - 1))
            {
                count ++;
                blueTotal += tempImage[h + i][w + j].rgbtBlue;
                greenTotal += tempImage[h + i][w + j].rgbtGreen;
                redTotal += tempImage[h + i][w + j].rgbtRed;
            }
        }
    }
    image[h][w].rgbtBlue = maxByte(round(blueTotal / (float) count));
    image[h][w].rgbtGreen = maxByte(round(greenTotal / (float) count));
    image[h][w].rgbtRed = maxByte(round(redTotal / (float) count));
}

void computeEdgePixels(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE tempImage[height][width], \
                       int h, int w, int gX[3][3], int gY[3][3])
{
    PIXELINT tempX = {0};
    PIXELINT tempY = {0};

    // iterate Sobel operator over 3 x 3 grid
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int tempGX = 0;
            int tempGY = 0;

            // get gX and gY as long as we are not beyond the boundary of the image
            if (inGrid(h + i, 0, height - 1) && inGrid(w + j, 0, width - 1))
            {
                tempGX = gX[i + 1][j + 1];
                tempGY = gY[i + 1][j + 1];
            }
            // accumulate the adjusted values for the 3 * 3 grid
            tempX.blue += tempImage[h + i][w + j].rgbtBlue * tempGX;
            tempX.green += tempImage[h + i][w + j].rgbtGreen * tempGX;
            tempX.red += tempImage[h + i][w + j].rgbtRed * tempGX;
            tempY.blue += tempImage[h + i][w + j].rgbtBlue * tempGY;
            tempY.green += tempImage[h + i][w + j].rgbtGreen * tempGY;
            tempY.red += tempImage[h + i][w + j].rgbtRed * tempGY;
        }
    }

    // compute the final values for this pixel
    image[h][w].rgbtBlue = maxByte((int) round(sqrt(pow((double) tempX.blue, 2.0) + pow((double) tempY.blue, 2.0))));
    image[h][w].rgbtGreen = maxByte((int) round(sqrt(pow((double) tempX.green, 2.0) + pow((double) tempY.green, 2.0))));
    image[h][w].rgbtRed = maxByte((int) round(sqrt(pow((double) tempX.red, 2.0) + pow((double) tempY.red, 2.0))));
}

bool inGrid(int position, int min, int max)
{
    // returns true if the position is within the boundaries of min and max
    if (position < min || position > max)
    {
        return false;
    }
    return true;
}

BYTE maxByte(int pixel)
{
    // converts int pixel to byte and sets max value of 255
    if (pixel > 255)
    {
        return (BYTE) 255;
    }
    return (BYTE) pixel;
}

void copyImageArray(int height, int width, RGBTRIPLE copyFrom[height][width], RGBTRIPLE copyTo[height][width])
{
    // copies an image array
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copyTo[h][w] = copyFrom[h][w];
        }
    }
}