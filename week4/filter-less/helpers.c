#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int x = 0; x < width; x++)
        {
            int gray_value = round((image[i][x].rgbtBlue + image[i][x].rgbtGreen + image[i][x].rgbtRed) / 3.0);
            image[i][x].rgbtBlue = gray_value;
            image[i][x].rgbtGreen = gray_value;
            image[i][x].rgbtRed = gray_value;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int x = 0; x < width; x++)
        {
            int sepiaRed = round(.393 * image[i][x].rgbtRed + .769 * image[i][x].rgbtGreen + .189 * image[i][x].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][x].rgbtRed + .686 * image[i][x].rgbtGreen + .168 * image[i][x].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][x].rgbtRed + .534 * image[i][x].rgbtGreen + .131 * image[i][x].rgbtBlue);

            // If the value exceed put it equal 255.
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][x].rgbtBlue = sepiaBlue;
            image[i][x].rgbtGreen = sepiaGreen;
            image[i][x].rgbtRed = sepiaRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // So any pixels on the left side of the image should end up on the right, and vice versa
    /*
    Note that all of the original pixels of the original image will still be present in the reflected image,
    it’s just that those pixels may have rearranged to be in a different place in the image.
    */
    for (int i = 0; i < height; i++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            // We want to reverse the first pixel in row with last pixel in row
            RGBTRIPLE tmp = image[i][x];
            image[i][x] = image[i][width - x - 1];
            image[i][width - x - 1] = tmp;
        }
    }
}
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of the input image
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            copy[row][col] = image[row][col];
        }
    }

    // loop over each pixel in the image
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // initialize a sum and count for each color channel
            int r_sum = 0, g_sum = 0, b_sum = 0, count = 0;
            // loop over each neighboring pixel and update the sum and count for each color channel
            for (int i = -1; i <= 1; i++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    int new_row = row + i;
                    int new_col = col + x;
                    // check that there are no out row or column out of image.
                    if (new_row >= 0 && new_row < height && new_col >= 0 && new_col < width)
                    {
                        r_sum += copy[new_row][new_col].rgbtRed;
                        g_sum += copy[new_row][new_col].rgbtGreen;
                        b_sum += copy[new_row][new_col].rgbtBlue;
                        count++;
                    }
                }
            }
            // compute the average color for the pixel and update the image
            image[row][col].rgbtRed = round(r_sum / (float) count);
            image[row][col].rgbtGreen = round(g_sum / (float) count);
            image[row][col].rgbtBlue = round(b_sum / (float) count);
        }
    }
}