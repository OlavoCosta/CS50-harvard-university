#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// The player who types the word with the highest score, according to the points table, wins.

// ALPHABET--> (A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q   R  S  T  U  V  W  X  Y  Z).
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void){
    // words typed by players.
    string word1 = get_string("Player 1 type your word: ");
    string word2 = get_string("Player 2 type your word: ");

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // step: will check which player won or if there was a tie
    if(score1 > score2){
        printf("Player 1 wins!\n");
    }
    else if(score1 < score2){
        printf("Player 2 wins!\n");
    }else{
        printf("Tie, try again!\n");
    }
}

int compute_score(string word){
    //step: checking punctuation according to the alphabet
    int score = 0;

    for(int i = 0, len = strlen(word); i < len; i++){
        // using the functions to return a boolean
        if (isupper(word[i])){
            score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i])){
            score += POINTS[word[i] - 'a'];
        }
    }

    return score;
}