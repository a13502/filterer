#include "helpers.h"
#include<math.h>
#include<stdio.h>
#include<cs50.h>
int i, j;
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for(i = 0; i <= height; i++)
    {
        for(j = 0;j <= width; j++)
        {
            int Red = image[i][j].rgbtRed;
            int Green = image[i][j].rgbtGreen;
            int Blue = image[i][j].rgbtBlue;

            avg = round((Red+Green+Blue)/(float)3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sr, sg, sb;
     for(i = 0; i <= height; i++)
    {
        for(j = 0;j <= width; j++)
        {
            sr = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            sg = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            sb = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));
            if(sr >255)
            {
                image[i][j].rgbtRed = 255;
                image[i][j].rgbtBlue = sb;
                image[i][j].rgbtGreen = sg;
            }
            else if(sb>255)
            {
                image[i][j].rgbtBlue = 255;
                image[i][j].rgbtRed = sr;
                image[i][j].rgbtGreen = sg;
            }
            else if(sg>255)
            {
                image[i][j].rgbtGreen = 255;
                image[i][j].rgbtRed = sr;
                image[i][j].rgbtBlue = sb;
            }
            else
            {
                image[i][j].rgbtRed = sr;
                image[i][j].rgbtBlue = sb;
                image[i][j].rgbtGreen = sg;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(i=0;i<height;i++)
    {
        for(j = 0; j < width/2; j++)
        {
            int tr = image[i][j].rgbtRed;
            int tg = image[i][j].rgbtGreen;
            int tb = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = tr;
            image[i][width - j - 1].rgbtGreen = tg;
            image[i][width - j - 1].rgbtBlue = tb;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
     RGBTRIPLE temp[height][width];

    for ( i = 0; i < height; i++)
    {
        for ( j = 0; j < width; j++)
        {
            int total_Red, total_Blue, total_Green;

            total_Red = total_Blue = total_Green = 0;

            float counter = 0.00;

            //Get the neighbouring pexels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    //check for valid neighbouring pexels
                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        continue;
                    }

                    //Get the image value
                    total_Red += image[currentX][currentY].rgbtRed;
                    total_Green += image[currentX][currentY].rgbtGreen;
                    total_Blue += image[currentX][currentY].rgbtBlue;

                    counter++;
                }
                temp[i][j].rgbtRed = round(total_Red / counter);
                temp[i][j].rgbtGreen = round(total_Green / counter);
                temp[i][j].rgbtBlue = round(total_Blue / counter);
            }
        }

    }

    //copy the blurr image to the original image
    for ( i = 0; i < height; i++)
    {
        for ( j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
