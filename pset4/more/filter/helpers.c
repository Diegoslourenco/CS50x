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


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx = 0;
    int gy = 0;
    int tmpBlue[height][width];
    int tmpGreen[height][width];
    int tmpRed[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                gx = 2 * image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                gy = 2 * image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                tmpBlue[i][j] = tmpBlue[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                gx = 2 * image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                gy = 2 * image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                tmpGreen[i][j] = tmpGreen[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                gx = 2 * image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                gy = 2 * image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                tmpRed[i][j] = tmpRed[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));
            }
            else if (i == 0 && j == width - 1)
            {
                gx = - 2 * image[i][j - 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue;
                gy = 2 * image[i + 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue;
                tmpBlue[i][j] = tmpBlue[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                gx = - 2 * image[i][j - 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen;
                gy = 2 * image[i + 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen;
                tmpGreen[i][j] = tmpGreen[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                gx = - 2 * image[i][j - 1].rgbtRed - image[i - 1][j - 1].rgbtRed;
                gy = 2 * image[i + 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed;
                tmpRed[i][j] = tmpRed[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));
            }
            else if (i == height - 1 && j == 0)
            {
                gx = 2 * image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                gy = - 2 * image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue;
                tmpBlue[i][j] = tmpBlue[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                gx = 2 * image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
                gy = - 2 * image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen;
                tmpGreen[i][j] = tmpGreen[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                gx = 2 * image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed;
                gy = - 2 * image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed;
                tmpRed[i][j] = tmpRed[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));
            }
            else if (i == height - 1 && j == width - 1)
            {
                gx = - 2 * image[i][j - 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue;
                gy = - 2 * image[i - 1][j].rgbtBlue - image[i - 1][j - 1].rgbtBlue;
                tmpBlue[i][j] = tmpBlue[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                gx = - 2 * image[i][j - 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen;
                gy = - 2 * image[i - 1][j].rgbtGreen - image[i - 1][j - 1].rgbtGreen;
                tmpGreen[i][j] = tmpGreen[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                gx = - 2 * image[i][j - 1].rgbtRed - image[i - 1][j - 1].rgbtRed;
                gy = - 2 * image[i - 1][j].rgbtRed - image[i - 1][j - 1].rgbtRed;
                tmpRed[i][j] = tmpRed[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));
            }
            else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                if (i == 0)
                {
                    gx = - 2 * image[i][j - 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    gy = image[i + 1][j - 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    tmpBlue[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                    gx = - 2 * image[i][j - 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen +
                        image[i + 1][j + 1].rgbtGreen;
                    gy = image[i + 1][j - 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    tmpGreen[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                    gx = - 2 * image[i][j - 1].rgbtRed - image[i + 1][j - 1].rgbtRed + 2 * image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    gy = image[i + 1][j - 1].rgbtRed + 2 * image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    tmpRed[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));
                }
                else if (i == height - 1)
                {
                    gx = - 2 * image[i][j - 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                    gy = - image[i - 1][j - 1].rgbtBlue - 2 * image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue;
                    tmpBlue[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                    gx = - 2 * image[i][j - 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen +
                        image[i - 1][j + 1].rgbtGreen;
                    gy = - image[i - 1][j - 1].rgbtGreen - 2 * image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen;
                    tmpGreen[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                    gx = - 2 * image[i][j - 1].rgbtRed - image[i - 1][j - 1].rgbtRed + 2 * image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed;
                    gy = - image[i - 1][j - 1].rgbtRed - 2 * image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed;
                    tmpRed[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));
                }
                else if (j == 0)
                {
                    gx = image[i - 1][j - 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    gy = - 2 * image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    tmpBlue[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                    gx = image[i - 1][j - 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    gy = - 2 * image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen +
                        image[i + 1][j + 1].rgbtGreen;
                    tmpGreen[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                    gx = image[i - 1][j - 1].rgbtRed + 2 * image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    gy = - 2 * image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed + 2 * image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    tmpRed[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));
                }
                else
                {
                    gx = - image[i - 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue;
                    gy = - image[i - 1][j - 1].rgbtBlue - 2 * image[i - 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue;
                    tmpBlue[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                    gx = - image[i - 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen;
                    gy = - image[i - 1][j - 1].rgbtGreen - 2 * image[i - 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                        2 * image[i + 1][j].rgbtGreen;
                    tmpGreen[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

                    gx = - image[i - 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed - image[i + 1][j - 1].rgbtRed;
                    gy = - image[i - 1][j - 1].rgbtRed - 2 * image[i - 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + 2 * image[i + 1][j].rgbtRed;
                    tmpRed[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));
                }
            }
            else
            {
            gx = - image[i - 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue +
                   image[i - 1][j - 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
            gy = - image[i - 1][j - 1].rgbtBlue - 2 * image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue +
                   image[i + 1][j - 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
            tmpBlue[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

            gx = - image[i - 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen +
                   image[i - 1][j - 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
            gy = - image[i - 1][j - 1].rgbtGreen - 2 * image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen +
                   image[i + 1][j - 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
            tmpGreen[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));

            gx = - image[i - 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed - image[i + 1][j - 1].rgbtRed +
                   image[i - 1][j - 1].rgbtRed + 2 * image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
            gy = - image[i - 1][j - 1].rgbtRed - 2 * image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed +
                   image[i + 1][j - 1].rgbtRed + 2 * image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
            tmpRed[i][j] = round((float)sqrt((float)(pow(gx, 2) + pow(gy, 2))));
            }
        }
    }
    return;
}