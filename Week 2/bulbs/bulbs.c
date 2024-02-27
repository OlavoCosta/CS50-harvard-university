#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void){
    int arr[8] = {0};

    //stage: You will read the typed text.
    string text = get_string("Enter your text: ");

    //stage: checking each letter of the typed word.
    for(int x = 0; x < strlen(text); x++){
        int val = text[x];
        int i = 0;
        int j = 7;

        while(i < BITS_IN_BYTE){
            arr[i] = val % 2;
            val = val / 2;
            i++;
        }
        
        //stage: loop that will invert the array.
        while(j >= 0){
            print_bulb(arr[j]);
            j--;
        }
        printf("\n");
    }

    return 0;
}

void print_bulb(int bit){
    if(bit == 0){
        // Dark emoji
        printf("\U000026AB");

    }else if(bit == 1){
        // Light emoji
        printf("\U0001F7E1");
    }
}