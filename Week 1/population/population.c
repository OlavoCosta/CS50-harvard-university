#include <cs50.h>
#include <stdio.h>

int main(void){
    int st, end, x, y, years = 0;

    // TODO: Prompt for start size
    do{
        st = get_int("Start Size: ");
    }while(st <= 8);

    // TODO: Prompt for end size
    do{
        end = get_int("End Size: ");
    }while(end < st);

    // TODO: Calculate number of years until we reach threshold
    for(years = 0; st < end; years++){
        x = st / 3;
        y = st / 4;
        st = st + x - y;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);

}