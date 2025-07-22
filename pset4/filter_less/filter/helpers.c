#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue);
            int avg = round((float)sum / 3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}
/*
if rgb are same value, you get a shade of grey.
lighter color = lighter shade of grey, darker color = darker shade of grey
calc avg pxl value as new value (round)
*/

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float r = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float g = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float b = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            image[i][j].rgbtRed = fmin(255, round(r));
            image[i][j].rgbtGreen = fmin(255, round(g));
            image[i][j].rgbtBlue = fmin(255, round(b));
        }
    }
    return;
}
/*
sepia formula (round): if value > 255, capp it to 255
 sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
 sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
 sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
*/

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int k, n;
    k = width / 2;
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        n = width - 1;
        for (int j = 0; j < k; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][n];
            image[i][n] = temp;
            n--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float avgR, avgG, avgB;
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];

            if (i == 0)
            {
                // top left corner
                if (j == 0)
                {
                    avgR = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed
                            + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / (float)4;
                    avgG = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen
                            + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / (float)4;
                    avgB = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue
                            + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / (float)4;

                    temp[i][j].rgbtRed = round(avgR);
                    temp[i][j].rgbtGreen = round(avgG);
                    temp[i][j].rgbtBlue = round(avgB);
                }
                // top right corner
                else if (j == width - 1)
                {
                    avgR = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed
                            + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / (float)4;
                    avgG = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen
                            + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / (float)4;
                    avgB = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue
                            + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / (float)4;

                    temp[i][j].rgbtRed = round(avgR);
                    temp[i][j].rgbtGreen = round(avgG);
                    temp[i][j].rgbtBlue = round(avgB);
                }
                // top edge pixels
                else if (j > 0 && j < width - 1)
                {
                    avgR = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed
                            + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / (float)6;
                    avgG = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen
                            + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / (float)6;
                    avgB = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue
                            + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / (float)6;

                    temp[i][j].rgbtRed = round(avgR);
                    temp[i][j].rgbtGreen = round(avgG);
                    temp[i][j].rgbtBlue = round(avgB);
                }
            }

            else if (i == height - 1)
            {
                // bottom left corner
                if (j == 0)
                {
                    avgR = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed
                            + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / (float)4;
                    avgG = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen
                            + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / (float)4;
                    avgB = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue
                            + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / (float)4;

                    temp[i][j].rgbtRed = round(avgR);
                    temp[i][j].rgbtGreen = round(avgG);
                    temp[i][j].rgbtBlue = round(avgB);
                }
                //bottom right corner
                else if (j == width - 1)
                {
                    avgR = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed
                            + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / (float)4;
                    avgG = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen
                            + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / (float)4;
                    avgB = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue
                            + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / (float)4;

                    temp[i][j].rgbtRed = round(avgR);
                    temp[i][j].rgbtGreen = round(avgG);
                    temp[i][j].rgbtBlue = round(avgB);
                }
                // bottom edge
                else if (j > 0 && j < width - 1)
                {
                    avgR = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed
                            + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / (float)6;
                    avgG = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen
                            + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / (float)6;
                    avgB = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue
                            + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / (float)6;

                    temp[i][j].rgbtRed = round(avgR);
                    temp[i][j].rgbtGreen = round(avgG);
                    temp[i][j].rgbtBlue = round(avgB);
                }
            }
            else if (i > 0 && i < height - 1)
            {
                //left edge
                if (j == 0)
                {
                    avgR = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed
                            + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed
                            + image[i + 1][j].rgbtRed  + image[i + 1][j + 1].rgbtRed) / (float)6;
                    avgG = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen
                            + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen
                            + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / (float)6;
                    avgB = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue
                            + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue
                            + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / (float)6;

                    temp[i][j].rgbtRed = round(avgR);
                    temp[i][j].rgbtGreen = round(avgG);
                    temp[i][j].rgbtBlue = round(avgB);
                }
                //right edge
                else if (j == width - 1)
                {
                    avgR = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed
                            + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed
                            + image[i + 1][j].rgbtRed  + image[i + 1][j - 1].rgbtRed) / (float)6;
                    avgG = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen
                            + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen
                            + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / (float)6;
                    avgB = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue
                            + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue
                            + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / (float)6;

                    temp[i][j].rgbtRed = round(avgR);
                    temp[i][j].rgbtGreen = round(avgG);
                    temp[i][j].rgbtBlue = round(avgB);
                }
                //middle
                else if (j > 0 && j < width - 1)
                {
                    avgR = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed
                            + image[i + 1][j].rgbtRed  + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed
                            + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / (float)9;
                    avgG = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen
                            + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen
                            + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / (float)9;
                    avgB = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue
                            + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue
                            + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / (float)9;

                    temp[i][j].rgbtRed = round(avgR);
                    temp[i][j].rgbtGreen = round(avgG);
                    temp[i][j].rgbtBlue = round(avgB);
                }
            }
        }
    }
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n] = temp[m][n];
        }
    }
    return;
}
/*
box blur
new value = average of values of all pixels around a pixel, including it (forming a 3x3 box)
avgR
avgG
avgB

1   2   3   4
5   6   7   8
9   10  11  12
13  14  15  16

values for pixel 6 would be by averaging original color values of pixels 1, 2, 3, 5, 6, 7, 9, 10, and 11
*/


// filter more:
// Detect edges; computer each new channel value as the sq rt of Gx^2 + gy^2; capp >255
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int avgR, avgG, avgB;
    int gxr, gxg, gxb, gyr, gyg, gyb;
    RGBTRIPLE temp[height][width];
    RGBTRIPLE grid[3][3];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // create a 3x3 grid
            for (int l = 0; l < 3; l++)
            {
                for (int m = 0; m < 3; m++)
                {
                    if ((i + (l - 1) < 0) || (j + (m - 1) < 0) || (i + (l - 1) > height - 1) || (j + (m - 1) > width - 1 ))
                    {
                        grid[l][m].rgbtRed = grid[l][m].rgbtGreen = grid[l][m].rgbtBlue = 0;
                    }
                    else
                    {
                        grid[l][m] = temp[i + (l - 1)][j + (m - 1)];
                    }
                }
            }

            gxr = gyr = gxg = gyg = gxb = gyb = 0;
            for (int l = 0; l < 3; l++)
            {
                for (int m = 0; m < 3; m++)
                {
                    gxr += grid[l][m].rgbtRed * gx[l][m];
                    gxg += grid[l][m].rgbtGreen * gx[l][m];
                    gxb += grid[l][m].rgbtBlue * gx[l][m];

                    gyr += grid[l][m].rgbtRed * gy[l][m];
                    gyg += grid[l][m].rgbtGreen * gy[l][m];
                    gyb += grid[l][m].rgbtBlue * gy[l][m];
                }
            }

            avgR = round(sqrt(pow(gxr, 2) + pow(gyr, 2)));
            avgG = round(sqrt(pow(gxg, 2) + pow(gyg, 2)));
            avgB = round(sqrt(pow(gxb, 2) + pow(gyb, 2)));

            image[i][j].rgbtRed = fmin(255, avgR);
            image[i][j].rgbtGreen = fmin(255, avgG);
            image[i][j].rgbtBlue = fmin(255, avgB);
        }
    }
    return;
}
/*
./filter -g images/yard.bmp zg.bmp
./filter -s images/courtyard.bmp zs.bmp
./filter -b images/stadium.bmp zb.bmp
./filter -b images/tower.bmp zb.bmp
./filter -e images/tower.bmp ze.bmp

style50 helpers.c
check50 cs50/problems/2020/x/filter/less
check50 cs50/problems/2020/x/filter/more

submit50 cs50/problems/2020/x/filter/less


*/

