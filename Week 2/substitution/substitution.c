#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
    "This 26-character key means that A(the first letter of the alphabet) should be converted to N
    (the first character of the key), B(the second letter of the alphabet) should be converted to Q
    (the second character of the key),and so on. A message like HELLO, then, would be encrypted as FOLLE,
    replacing each of the letters according to the mapping determined by the key."
*/

// Example key, might be the string NQXPOMAFTRHLZGECYJIUWSKDVB.
int main(int argc, string argv[]){
    //Stage: accepts only one argument
    if(argc != 2){
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //Stage: checks validation the key
    if(strlen(argv[1]) != 26){
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string key = argv[1];
    int alphabet[26] = {0};

    for(int i = 0; i < 26; i++){
        alphabet[toupper(key[i]) - 'A']++;
    }

    //Checking the text for repeated letters
    for(int i = 0; i < 26; i++){
        
        if(alphabet[i] != 1){
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }

    //Stage: verification of the text entered by the user.
    string text = get_string("plaintext:  ");

    for(int x = 0, n = strlen(text); x < n; x++){

        if (isalpha(text[x])){
            if (isupper(text[x])){
                text[x] = toupper(key[text[x] - 'A']);
            }else{
                text[x] = tolower(key[text[x] - 'a']);
            }
        }
    }

    printf("ciphertext: %s\n", text);

    return 0;
}