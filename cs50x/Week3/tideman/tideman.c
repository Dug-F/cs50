#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool has_cycle(pair origin_node, int current_node);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // rank: index of candidate being entered
    // name: name of candidate being entered
    // ranks: passed array containing ranked candidates entered

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // update global preferences array to increment count of voters who prefer ith candidate over jth
    // e.g. if voter prefers candidate 2 over candidate 3, preferences[2][3] would be incremented

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // look at all pairs of candidates
    // for each pair, compare score of i vs j to j vs i.  If there is a winner, put it in the pairs array

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] == preferences[j][i])
            {
                continue;
            }

            pair head_to_head;

            if (preferences[i][j] > preferences[j][i])
            {
                head_to_head.winner = i;
                head_to_head.loser = j;
            }
            else
            {
                head_to_head.winner = j;
                head_to_head.loser = i;
            }

            pairs[pair_count] = head_to_head;
            pair_count++;
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // implement bubble sort

    pair temp;
    bool updated;

    for (int i = 0; i < pair_count - 1; i++)
    {
        updated = false;
        for (int j = i + 1; j < pair_count; j++)
        {
            int margin[2];
            margin[0] = preferences[pairs[i].winner] - preferences[pairs[i].loser];
            margin[1] = preferences[pairs[j].winner] - preferences[pairs[j].loser];
            if (margin[1] < margin[0])
            {
                temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
                updated = true;
            }
        }
        if (!updated)
        {
            break;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // for each candidate i
    // check if no locks in locked [*][i] are true

    bool winner;

    for (int i = 0; i < candidate_count; i++)
    {
        winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (locked[j][i])
            {
                winner = false;
                break;
            }
        }

        if (winner)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}

bool has_cycle(pair origin_node, int current_node)
{
    // need to go tail to head (winner to loser) away from the origin round the cycle, as the lock is at the tail end
    // if we get back round to find a node origin head to tail (loser to winner), then we have found a cycle and we can stop.
    // We move to the next node only if we find a lock in place in locked.
    // We are walking down a decision tree, at each new node spawning child candidate nodes
    // the link between origin head to tail does not have a lock, so we need to check that before checking locks

    // for each node (index i)  in candidates
    //     if current_node to i is origin loser to winner
    //         return true
    //     if lock in place for current_node to i
    //         if has_cycle(origin_node, i)
    //             return true

    for (int i = 0; i < candidate_count; i++)
    {
        if (i == origin_node.winner && current_node == origin_node.loser)
        {
            return true;
        }
        if (locked[i][current_node] && has_cycle(origin_node, i))
        {
            return true;
        }
    }

    return false;
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!has_cycle(pairs[i], pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}