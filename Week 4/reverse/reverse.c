#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[]){
    // Ensure proper usage

    // TODO #1
    if(argc < 1 || argc > 3){   // if different, restart the program

        printf("Usage ./reverse input.wav output.wav\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1]; //input file
    char *outfile = argv[2]; // output file

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(infile, "rb"); // Open the inserted file in read mode.
    if(input == NULL){
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // Read header into an array
    // TODO #3
    WAVHEADER head;
    fread(&head, sizeof(WAVHEADER), 1, input); // Read file header

    // Use check_format to ensure WAV format
    // TODO #4
    if(!check_format(head)){ // check file TODO#3

        printf("The input you entered is not a WAV.\n");
        fclose(input);
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(outfile, "wb");

    //Ensure a valid output file
    if(output == NULL){
        fclose(input);
        printf("Could not create %s.\n", outfile);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&head, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(head);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[block_size];

    // Put the fseek() pointer back twice, once at the previous location, once to go to the new location
    for(fseek(input, 0 - block_size, SEEK_END); ftell(input) > sizeof(head) - block_size; fseek(input, 0 - (block_size * 2), SEEK_CUR)){

        fread(&buffer, block_size, 1, input);
        fwrite(&buffer, block_size, 1, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}

int check_format(WAVHEADER header){
    // TODO #4
    int format[4] = {'W', 'A', 'V', 'E'}; // setting the array size to the number of characters entered

    for(int i = 0; i < 4; i++){
        if(header.format[i] != format[i]){
            return 0;
        }
    }

    return 1;
}

int get_block_size(WAVHEADER header){
    // TODO #7
    return header.numChannels * (header.bitsPerSample / 8); //block size in bytes
}