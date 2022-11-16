#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // if candidate name matches passed name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // set preferences for voter and rank to index of candidate
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{

    // initialise vote count for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    //for each voter, add votes of first non-eliminated candidate to candidate's vote count
    int candidate_index;
    // iterate for each voter
    for (int i = 0; i < voter_count; i++)
    {
        // iterate for each preference
        for (int j = 0; j < candidate_count; j++)
        {
            // get candidate index for voter and preference
            candidate_index = preferences[i][j];
            if (!candidates[candidate_index].eliminated)
            {
                // increment vote for candidate
                candidates[candidate_index].votes++;
                break;
            }
        }
    }

    return;
}

// void tabulate(void)
// {
//     for (int i = 0; i < voter_count; i++)
//     {
//         if (candidates[preferences[i][0]].eliminated == false)
//         {
//             candidates[preferences[i][0]].votes++;
//             continue;
//         }
//         for (int j = 0; j < candidate_count - 1; j++)
//         {
//             if (candidates[preferences[i][j]].eliminated == true)
//             {
//                 if (candidates[preferences[i][j + 1]].eliminated == false)
//                 {
//                     candidates[preferences[i][j + 1]].votes++;
//                     break;
//                 }
//             }
//         }
//     }
// }


// Print the winner of the election, if there is one
bool print_winner(void)
{
    // iterate for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // if candidate has more than 50% of the votes
        if (candidates[i].votes > voter_count / (float) 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count + 1;
    // iterate for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            // if candidate has fewer votes than currently identified minimum
            if (candidates[i].votes < min)
            {
                // update minimum with candidate votes
                min = candidates[i].votes;
            }
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // iterate for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            // if any candidate votes differs from min
            if (candidates[i].votes != min)
            {
                return false;
            }
        }
    }
    // all non-eliminated candidates must have the same vote score
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // iterate for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate is not already eliminated
        if (!candidates[i].eliminated)
        {
            // if candidate score matches the passed min score
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
            }
        }
    }
    return;
}