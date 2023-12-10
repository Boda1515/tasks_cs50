#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int x = 0; x < width; x++)
        {
            int grayscale = round((image[i][x].rgbtRed + image[i][x].rgbtGreen + image[i][x].rgbtBlue) / (float) 3.0);
            image[i][x].rgbtRed = grayscale;
            image[i][x].rgbtGreen = grayscale;
            image[i][x].rgbtBlue = grayscale;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            // create a swap
            RGBTRIPLE tmp = image[i][x];
            image[i][x] = image[i][width - x - 1];
            image[i][width - x - 1] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy from image.
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int x = 0; x < width; x++)
        {
            copy[i][x] = image[i][x];
        }
    }
    // Loop for all pixels in image.
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Initialize the RGBTRIPLE components, count variable to count the number of pixels we are divid it.
            int r_s = 0, g_s = 0, b_s = 0, count = 0;

            // Loop to calc the sirounding pixels
            // In this loop we take three steps berfor the number, the number him self, the number after the number
            for (int i = -1; i <= 1; i++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    // The new row to take his number and so forth for column.
                    int new_row = row - i;
                    int new_col = col - x;

                    // Check if any new(row, col) out of image.
                    if (new_row >= 0 && new_row < height && new_col < width && new_col >= 0)
                    {
                        r_s += copy[new_row][new_col].rgbtRed;
                        g_s += copy[new_row][new_col].rgbtGreen;
                        b_s += copy[new_row][new_col].rgbtBlue;
                        count++;
                    }
                }
            }
            image[row][col].rgbtRed = round(r_s / (float) count);
            image[row][col].rgbtGreen = round(g_s / (float) count);
            image[row][col].rgbtBlue = round(b_s / (float) count);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Load the input image and add a border of black pixels around the edges.
    // Create a copy from image.
    RGBTRIPLE copy[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int x = 0; x < width + 2; x++)
        {
            if (i == 0 || i == height + 1 || x == 0 || x == width + 1)
            {
                copy[i][x].rgbtRed = 0x00;
                copy[i][x].rgbtGreen = 0x00;
                copy[i][x].rgbtBlue = 0x00;
            }
            else
            {
                copy[i][x] = image[i - 1][x - 1];
            }
        }
    }
    // Create two 3x3 Sobel kernels, one for detecting edges in the x direction and another for detecting edges in the y direction.
    int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // Loop through each pixel of the image (excluding the border pixels) and for each pixel:
    for (int row = 1; row < height + 1; row++)
    {
        for (int col = 1; col < width + 1; col++)
        {
            // Create a 3x3 matrix of the pixel values surrounding the current pixel.
            RGBTRIPLE Gx[3][3];
            RGBTRIPLE Gy[3][3];
            for (int i = -1; i <= 1; i++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    Gx[i + 1][x + 1].rgbtRed = copy[row + i][col + x].rgbtRed;
                    Gx[i + 1][x + 1].rgbtGreen = copy[row + i][col + x].rgbtGreen;
                    Gx[i + 1][x + 1].rgbtBlue = copy[row + i][col + x].rgbtBlue;

                    Gy[i + 1][x + 1].rgbtRed = copy[row + i][col + x].rgbtRed;
                    Gy[i + 1][x + 1].rgbtGreen = copy[row + i][col + x].rgbtGreen;
                    Gy[i + 1][x + 1].rgbtBlue = copy[row + i][col + x].rgbtBlue;
                }
            }
            // Compute Gx and Gy values for each color channel using the Sobel kernels.
            int redX = 0, greenX = 0, blueX = 0;
            int r_y = 0, g_y = 0, b_y = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    redX += Gx[k][l].rgbtRed * sobelY[k][l];
                    greenX += Gx[k][l].rgbtGreen * sobelY[k][l];
                    blueX += Gx[k][l].rgbtBlue * sobelY[k][l];

                    r_y += Gy[k][l].rgbtRed * sobelX[k][l];
                    g_y += Gy[k][l].rgbtGreen * sobelX[k][l];
                    b_y += Gy[k][l].rgbtBlue * sobelX[k][l];
                }
            }
            // Combine the Gx and Gy values for each color channel using the formula: sqrt(Gx^2 + Gy^2).
            int RED = round(sqrt(pow(redX, 2) + pow(r_y, 2)));
            int GREEN = round(sqrt(pow(greenX, 2) + pow(g_y, 2)));
            int BLUE = round(sqrt(pow(blueX, 2) + pow(b_y, 2)));
            // Cap the combined value at 255.
            if (RED > 255)
            {
                RED = 255;
            }
            if (GREEN > 255)
            {
                GREEN = 255;
            }
            if (BLUE > 255)
            {
                BLUE = 255;
            }
            // Update the pixel values of the original image.
            image[row - 1][col - 1].rgbtRed = RED;
            image[row - 1][col - 1].rgbtGreen = GREEN;
            image[row - 1][col - 1].rgbtBlue = BLUE;
        }
    }
}