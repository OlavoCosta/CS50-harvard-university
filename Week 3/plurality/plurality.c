#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct{
    string name;
    int votes;
}candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void candibubble(void);

int main(int argc, string argv[]){
    //Stage: if you don't enter the candidate's name print it out:
    if(argc < 2){
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    if(candidate_count > MAX){
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for(int i = 0; i < candidate_count; i++){
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for(int i = 0; i < voter_count; i++){
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name)){
            printf("Invalid vote.\n");
        }
    }

    // calls the candibubble function for sorting.
    candibubble();

    // Display winner of election
    print_winner();
}

// Update the vote totals with a new vote and if the string equals the candidate's name return true
bool vote(string name){
    int i = 0;

    while(i < candidate_count){
        if (strcmp(name, candidates[i].name) == 0){
            candidates[i].votes++;
            return true;
        }
        i++;
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void){
    int winnervt = candidates[0].votes;
    int i = 1;
    int j = 0;

    //Stage: starting votes with a value of 0, then it will update the value since it checks all candidates.
    while(i < candidate_count){

        if(candidates[i].votes > winnervt){
            winnervt = candidates[i].votes;
        }
        ++i;
    }

    // Printing winners
    while(j < candidate_count){
        if (candidates[j].votes == winnervt)
        {
            printf("%s\n", candidates[j].name);
        }
        ++j;
    }

    return;
}

//step: responsible for grading the candidates, method used in lab 3 classification.
void candibubble(void){
    int signal = 0;
    int struvotes = 0;
    string struname;

    // performs at least once.
    do{
        int i = 0;

        while(i < candidate_count - 1){
            // checks the order of the candidates scores.
            if(candidates[i].votes < candidates[i + 1].votes){
                struname = candidates[i].name;
                struvotes = candidates[i].votes;

                candidates[i].name = candidates[i + 1].name;
                candidates[i].votes = candidates[i + 1].votes;

                candidates[i + 1].name = struname;
                candidates[i + 1].votes = struvotes;
                signal = 1;
            }
            i++;
        }

    }while(signal == 1);
    
    return;
}