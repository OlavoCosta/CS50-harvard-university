#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

bool isperiod(char letter);
int count_words(string text);
int count_letters(string text);
int count_sentences(string text);
float count_scores(int words, int letters, int sentences);
void print_score(float score);

int main(void){
    // collects user information
    string text = get_string("Text: ");

    // calculate the function letter, word, sentence count.
    int words = count_words(text);
    int letters = count_letters(text);
    int sentences = count_sentences(text);

    float score = count_scores(words, letters, sentences);

    // Print the final result.
    print_score(score);

    return 0;
}

//Stage: ensures that you don't have multiple line spaces and doesn't allow you to start sentences with improper spacing.
int count_words(string text){
    int i = 0;
    int count = 1;

    while(i < strlen(text)){
        if(isspace(text[i])){
            count++;
        }
        i++;
    }

    return count;
}

// checks if the character value is between A to Z.
int count_letters(string text){
    int i = 0;
    int count = 0;

    while(i < strlen(text)){
        if(isalpha(text[i])){
            count ++;
        }
        i++;
    }

    return count;
}

//Stage: It also makes sure that you don't have multiple spaces between lines and doesn't allow you to start sentences with improper spacing.
int count_sentences(string text){
    int i = 0;
    int count = 0;

    while(i < strlen(text)){
        if(isperiod(text[i])){
            count++;
        }
        i++;
    }

    return count;
}

//Stage: checks whether the character value is a question mark, an exclamation mark, or a period, if so, it adds 1.
bool isperiod(char letter){
    return letter == '?' || letter == '!' || letter == '.';
}

//Stage: It calculates the average number of letters per word and average number of words per sentence.
float count_scores(int words, int letters, int sentences){
    // Calculating the Coleman-Liau index using the formula:
    float let = ((float) letters / (float) words) * 100.0;
    float sen = ((float) sentences / (float) words) * 100.0;

    return 0.0588 * let - 0.296 * sen - 15.8;
}

//Stage: checks and displays what level the grade is at.
void print_score(float score){
    // If number is less than 1
    if(score < 1.0){
        printf("Before Grade 1\n");
    }
    // If the index number is 16 or higher
    else if(score >= 16.0){
        printf("Grade 16+\n");
    }
    // if none of the above do.
    else{
        printf("Grade %i\n", (int) round(score));
    }
}