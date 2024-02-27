#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void){
    int weeks = get_int("Number of weeks taking CS50: ");   //GETS THE NUMBER OF WEEKS DOING CS50.
    int hours[weeks];

    for(int i = 0; i < weeks; i++){
        hours[i] = get_int("Week %i HW Hours: ", i);        //GETS THE AMOUNT OF HOURS IN EACH WEEK OF CS50.
    }

    char output;

    do{
        
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));

    }while(output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output){
    int i = 0;
    int tl = 0;

    //  First step is, add up all the indices in the array.
    while(i < weeks){
        tl += hours[i];
        i++;
    }

    // if output == 'T', return the sum total, if not, divide and return average.
    if(output == 'T'){
        return (float) tl;
    }

    return (float) tl / weeks;
}