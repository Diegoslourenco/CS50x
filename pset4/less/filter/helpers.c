#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int tmp = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp  = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = tmp;
            image[i][j].rgbtGreen = tmp;
            image[i][j].rgbtRed = tmp;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaBlue = 0;
    int sepiaGreen = 0;
    int sepiaRed = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Verifying the Blue
            if (round(0.272 * (float)image[i][j].rgbtRed + 0.534 * (float)image[i][j].rgbtGreen + 0.131 * (float)image[i][j].rgbtBlue) < 255)
            {
                sepiaBlue = round(0.272 * (float)image[i][j].rgbtRed + 0.534 * (float)image[i][j].rgbtGreen + 0.131 * (float)image[i][j].rgbtBlue);
            }
            else
            {
                sepiaBlue = 255;
            }
            // Verifying the Green
            if (round(0.349 * (float)image[i][j].rgbtRed + 0.686 * (float)image[i][j].rgbtGreen + 0.168 * (float)image[i][j].rgbtBlue) < 255)
            {
                sepiaGreen = round(0.349 * (float)image[i][j].rgbtRed + 0.686 * (float)image[i][j].rgbtGreen + 0.168 * (float)image[i][j].rgbtBlue);
            }
            else
            {
                sepiaGreen = 255;
            }
            //Verifying the Red
            if (round(0.393 * (float)image[i][j].rgbtRed + 0.769 * (float)image[i][j].rgbtGreen + 0.189 * (float)image[i][j].rgbtBlue) < 255)
            {
                sepiaRed = round(0.393 * (float)image[i][j].rgbtRed + 0.769 * (float)image[i][j].rgbtGreen + 0.189 * (float)image[i][j].rgbtBlue);
            }
            else
            {
                sepiaRed = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tmpBlue[height][width];
    int tmpGreen[height][width];
    int tmpRed[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmpBlue[i][j] = image[i][(width - 1) - j].rgbtBlue;
            tmpGreen[i][j] = image[i][(width - 1) - j].rgbtGreen;
            tmpRed[i][j] = image[i][(width - 1) - j].rgbtRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmpBlue[i][j];
            image[i][j].rgbtGreen = tmpGreen[i][j];
            image[i][j].rgbtRed = tmpRed[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int tmpBlue[height][width];
    int tmpGreen[height][width];
    int tmpRed[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                tmpBlue[i][j] = round(((float)image[i][j].rgbtBlue + (float)image[i][j + 1].rgbtBlue + (float)image[i + 1][j].rgbtBlue +
                                       (float)image[i + 1][j + 1].rgbtBlue) / 4);
                tmpGreen[i][j] = round(((float)image[i][j].rgbtGreen + (float)image[i][j + 1].rgbtGreen + (float)image[i + 1][j].rgbtGreen +
                                        (float)image[i + 1][j + 1].rgbtGreen) / 4);
                tmpRed[i][j] = round(((float)image[i][j].rgbtRed + (float)image[i][j + 1].rgbtRed + (float)image[i + 1][j].rgbtRed +
                                      (float)image[i + 1][j + 1].rgbtRed) / 4);
            }
            else if (i == 0 && j == width - 1)
            {
                tmpBlue[i][j] = round(((float)image[i][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i + 1][j].rgbtBlue +
                                       (float)image[i + 1][j - 1].rgbtBlue) / 4);
                tmpGreen[i][j] = round(((float)image[i][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i + 1][j].rgbtGreen +
                                        (float)image[i + 1][j - 1].rgbtGreen) / 4);
                tmpRed[i][j] = round(((float)image[i][j].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i + 1][j].rgbtRed +
                                      (float)image[i + 1][j - 1].rgbtRed) / 4);
            }
            else if (i == height - 1 && j == 0)
            {
                tmpBlue[i][j] = round(((float)image[i][j].rgbtBlue + (float)image[i][j + 1].rgbtBlue + (float)image[i - 1][j].rgbtBlue +
                                       (float)image[i - 1][j + 1].rgbtBlue) / 4);
                tmpGreen[i][j] = round(((float)image[i][j].rgbtGreen + (float)image[i][j + 1].rgbtGreen + (float)image[i - 1][j].rgbtGreen +
                                        (float)image[i - 1][j + 1].rgbtGreen) / 4);
                tmpRed[i][j] = round(((float)image[i][j].rgbtRed + (float)image[i][j + 1].rgbtRed + (float)image[i - 1][j].rgbtRed +
                                      (float)image[i - 1][j + 1].rgbtRed) / 4);
            }
            else if (i == height - 1 && j == width - 1)
            {
                tmpBlue[i][j] = round(((float)image[i][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i - 1][j].rgbtBlue +
                                       (float)image[i - 1][j - 1].rgbtBlue) / 4);
                tmpGreen[i][j] = round(((float)image[i][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i - 1][j].rgbtGreen +
                                        (float)image[i - 1][j - 1].rgbtGreen) / 4);
                tmpRed[i][j] = round(((float)image[i][j].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i - 1][j].rgbtRed +
                                      (float)image[i - 1][j - 1].rgbtRed) / 4);
            }
            else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                if (i == 0)
                {
                    tmpBlue[i][j] = round(((float)image[i][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue +
                                           (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue + (float)image[i][j + 1].rgbtBlue) / 6);
                    tmpGreen[i][j] = round(((float)image[i][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen +
                                            (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen + (float)image[i][j + 1].rgbtGreen) / 6);
                    tmpRed[i][j] = round(((float)image[i][j].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i + 1][j - 1].rgbtRed +
                                          (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j + 1].rgbtRed + (float)image[i][j + 1].rgbtRed) / 6);
                }
                else if (i == height - 1)
                {
                    tmpBlue[i][j] = round(((float)image[i][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue +
                                           (float)image[i - 1][j].rgbtBlue + (float)image[i - 1][j + 1].rgbtBlue + (float)image[i][j + 1].rgbtBlue) / 6);
                    tmpGreen[i][j] = round(((float)image[i][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen +
                                            (float)image[i - 1][j].rgbtGreen + (float)image[i - 1][j + 1].rgbtGreen + (float)image[i][j + 1].rgbtGreen) / 6);
                    tmpRed[i][j] = round(((float)image[i][j].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i - 1][j - 1].rgbtRed +
                                          (float)image[i - 1][j].rgbtRed + (float)image[i - 1][j + 1].rgbtRed + (float)image[i][j + 1].rgbtRed) / 6);
                }
                else if (j == 0)
                {
                    tmpBlue[i][j] = round(((float)image[i][j].rgbtBlue + (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue +
                                           (float)image[i][j + 1].rgbtBlue + (float)image[i - 1][j + 1].rgbtBlue + (float)image[i - 1][j].rgbtBlue) / 6);
                    tmpGreen[i][j] = round(((float)image[i][j].rgbtGreen + (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen +
                                            (float)image[i][j + 1].rgbtGreen + (float)image[i - 1][j + 1].rgbtGreen + (float)image[i - 1][j].rgbtGreen) / 6);
                    tmpRed[i][j] = round(((float)image[i][j].rgbtRed + (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j + 1].rgbtRed +
                                          (float)image[i][j + 1].rgbtRed + (float)image[i - 1][j + 1].rgbtRed + (float)image[i - 1][j].rgbtRed) / 6);
                }
                else
                {
                    tmpBlue[i][j] = round(((float)image[i][j].rgbtBlue + (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue +
                                           (float)image[i][j - 1].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue + (float)image[i - 1][j].rgbtBlue) / 6);
                    tmpGreen[i][j] = round(((float)image[i][j].rgbtGreen + (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen +
                                            (float)image[i][j - 1].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen + (float)image[i - 1][j].rgbtGreen) / 6);
                    tmpRed[i][j] = round(((float)image[i][j].rgbtRed + (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j - 1].rgbtRed +
                                          (float)image[i][j - 1].rgbtRed + (float)image[i - 1][j - 1].rgbtRed + (float)image[i - 1][j].rgbtRed) / 6);
                }
            }
            else
            {
                tmpBlue[i][j] = round(((float)image[i][j].rgbtBlue + (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue +
                                       (float)image[i][j - 1].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue + (float)image[i - 1][j].rgbtBlue +
                                       (float)image[i - 1][j + 1].rgbtBlue + (float)image[i][j + 1].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue) / 9);
                tmpGreen[i][j] = round(((float)image[i][j].rgbtGreen + (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen +
                                        (float)image[i][j - 1].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen + (float)image[i - 1][j].rgbtGreen +
                                        (float)image[i - 1][j + 1].rgbtGreen + (float)image[i][j + 1].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen) / 9);
                tmpRed[i][j] = round(((float)image[i][j].rgbtRed + (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j - 1].rgbtRed +
                                      (float)image[i][j - 1].rgbtRed + (float)image[i - 1][j - 1].rgbtRed + (float)image[i - 1][j].rgbtRed +
                                      (float)image[i - 1][j + 1].rgbtRed + (float)image[i][j + 1].rgbtRed + (float)image[i + 1][j + 1].rgbtRed) / 9);
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmpBlue[i][j];
            image[i][j].rgbtGreen = tmpGreen[i][j];
            image[i][j].rgbtRed = tmpRed[i][j];
        }
    }
    return;
}
