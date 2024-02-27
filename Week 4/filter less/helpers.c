#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]){
    float avg = 0;

    // repeat for all pixels
    for(int i = 0; i < height; i++){ //y
        for(int j = 0; j < width; j++){ //x
        
            // calculate greyscale average
            avg = round((image[i][j].rgbtBlue + image[i][j]. rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // replace the pixels by the average value
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]){
    float sepiaRed, sepiaGreen, sepiaBlue;

    // repeat for all pixels
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            
            // calculate the sepia values
            sepiaRed = (.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = (.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = (.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // replace the pixels by the average value using ternary expression
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : (int) round(sepiaBlue);
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : (int) round(sepiaGreen);
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : (int) round(sepiaRed);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]){
    // RGBTRIPLE present in struct
    RGBTRIPLE temp[width];
    int temp_index = width - 1;

    for(int y = 0; y < height; y++){
        // store RGBTRIPPLE in reverse order and place temp values into image
        for(int x = 0; x < width; x++){
            temp[temp_index] = image[y][x];
            temp_index--;
        }
        temp_index = width - 1;

        for(int x = 0; x < width; x++){
            image[y][x] = temp[x];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]){
    RGBTRIPLE temp[height][width];

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            float colBlue = 0;
            float colGreen = 0;
            float colRed = 0;
            float counter = 0;

            for(int a = -1; a < 2; a++){
                for(int b = -1; b < 2; b++){

                    if(i + a < 0 || i + a > height - 1){
                        continue;
                    }

                    if(j + b < 0 || j + b > width - 1){
                        continue;
                    }

                    colBlue += image[i + a][j + b].rgbtBlue;
                    colGreen += image[i + a][j + b].rgbtGreen;
                    colRed += image[i + a][j + b].rgbtRed;
                    counter++;
                }
            }

            temp[i][j].rgbtBlue = round(colBlue / counter);
            temp[i][j].rgbtGreen = round(colGreen / counter);
            temp[i][j].rgbtRed = round(colRed / counter);
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
