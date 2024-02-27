#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width]){
    // Change all black pixels to a color of your choosing
    int i = 0;
    int j = 0;

    while(i < height){
        while(j < width){

            // Make black pixels turn red
            if(image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00){
                
                image[i][j].rgbtRed = 0xff;
            }
            j++;
        }
        i++;
    }
}
