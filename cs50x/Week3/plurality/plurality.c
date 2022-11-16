#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // iterate through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if entered name = candidate name
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes ++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winners [candidate_count];
    int winner_count = 0;
    int winning_score = 0;

    // iterate through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if vote for this candidate equals the current winning score
        if (candidates[i].votes == winning_score)
        {
            // add candidate to winners array
            winner_count += 1;
            winners[winner_count - 1] = i;
        }
        // if vote for this candidate is a new winning score
        else if (candidates[i].votes > winning_score)
        {
            // reset the winners array with this candidate
            winner_count = 1;
            winners[winner_count - 1] = i;
            winning_score = candidates[i].votes;
        }
    }

    // iterate through winners array
    for (int i = 0; i < winner_count; i++)
    {
        // print candidate name from candidates array, indexed by the index saved in winners array
        printf("%s\n", candidates[winners[i]].name);
    }

    return;
}