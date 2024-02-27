#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //this program will ask for your name
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}