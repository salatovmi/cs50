#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < width; a++)
        {
            float mid = round((image[i][a].rgbtBlue + image[i][a].rgbtGreen + image[i][a].rgbtRed) / 3.0);
            image[i][a].rgbtBlue = image[i][a].rgbtGreen = image[i][a].rgbtRed = mid;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < width; a++)
        {
            BYTE originalBlue = image[i][a].rgbtBlue;
            BYTE originalGreen = image[i][a].rgbtGreen;
            BYTE originalRed = image[i][a].rgbtRed;
            if (round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue) > 255)
            {
                image[i][a].rgbtBlue = 255;
            }
            else image[i][a].rgbtBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue) > 255)
            {
                image[i][a].rgbtGreen = 255;
            }
            else image[i][a].rgbtGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            if (round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue) > 255)
            {
                image[i][a].rgbtRed = 255;
            }
            else image[i][a].rgbtRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < width - 1 - a; a++)
        {
            RGBTRIPLE left = image[i][a];
            RGBTRIPLE right = image[i][width - 1 - a];
            image[i][a] = right;
            image[i][width - 1 - a] = left;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int c = 0; c < height; c++)
    {
        for (int d = 0; d < width; d++)
        {
            temp[c][d] = image[c][d];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < width; a++)
        {
            int rows[3];
            int cols[3];
            float row_count = 0.0;
            float col_count = 0.0;
            if (i == 0)
            {
                rows[0] = i;
                rows[1] = i + 1;
                row_count = 2.0;
            }
            else if (i == height - 1)
            {
                rows[0] = i - 1;
                rows[1] = i;
                row_count = 2.0;
            }
            else
            {
                rows[0] = i - 1;
                rows[1] = i;
                rows[2] = i + 1;
                row_count = 3.0;
            }
            if (a == 0)
            {
                cols[0] = a;
                cols[1] = a + 1;
                col_count = 2.0;
            }
            else if (a == width - 1)
            {
                cols[0] = a - 1;
                cols[1] = a;
                col_count = 2.0;
            }
            else
            {
                cols[0] = a - 1;
                cols[1] = a;
                cols[2] = a + 1;
                col_count = 3.0;
            }
            
            int blue_sum = 0;
            int green_sum = 0;
            int red_sum = 0;
            for (int h = 0; h < row_count; h++)
            {
                for (int w = 0 ; w < col_count; w++)
                {
                    blue_sum += temp[rows[h]][cols[w]].rgbtBlue;
                    green_sum += temp[rows[h]][cols[w]].rgbtGreen;
                    red_sum += temp[rows[h]][cols[w]].rgbtRed;
                }
            }
            image[i][a].rgbtBlue = round(blue_sum / (row_count * col_count));
            image[i][a].rgbtGreen = round(green_sum / (row_count * col_count));
            image[i][a].rgbtRed = round(red_sum / (row_count * col_count));
        }
    }
}