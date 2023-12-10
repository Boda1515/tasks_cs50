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
bool forms_cycle(int winner, int loser);

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int prefered = ranks[i];
            int not_prefered = ranks[j];
            preferences[prefered][not_prefered]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
        // A pair of candidates who are tied (one is not preferred over the other) should not be added to the array.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            //A pair of candidates who are not tied
            if (preferences[i][j] > preferences[j][i])
            {
                // add to the pair array
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            //A pair of candidates who are tied
            else if (preferences[i][j] < preferences[j][i])
            {
                // Not add to the array
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // sorting useing bubble sort algorithm.
    /*  Repeat n-1 times
        For i from 0 to n–2
            If numbers[i] and numbers[i+1] out of order
                Swap them
    */
   for (int i = 0; i < pair_count - 1; i++)
   {
        for (int j = 0; j < pair_count - 2; j++)
        {
            int strength1 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int strength2 = preferences[pairs[j+1].winner][pairs[j+1].loser] - preferences[pairs[j+1].loser][pairs[j+1].winner];
            if (strength1 < strength2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
   }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // initialize array of locked pairs to false
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    // lock non-cyclic pairs in descending order of strength
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        if (!forms_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
}

// helper function to check if adding edge forms a cycle
bool forms_cycle(int winner, int loser)
{
    // case base of the recursive function if the winner and loser are the same, we've formed a cycle
    if (winner == loser)
    {
        return true;
    }
    // Recursive case: Check for cycles by traversing the existing locked edges
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if this edge is locked
        if (locked[loser][i])
        {
            // Recursively check whether edges from this node form a cycle
            if (forms_cycle(winner, i))
            {
                // If we've formed a cycle
                return true;
            }
        }
    }
    // If we've traversed the graph without forming a cycle, return false
    return false;
}
// Print the winner of the election
void print_winner(void)
{
    // TODO
// Create an array to keep track of the number of incoming edges to each node
    int incoming_edges[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        incoming_edges[i] = 0;
    }

    // Count incoming edges for each node by looping through the locked graph and incrementing the count
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                incoming_edges[i]++;
            }
        }
    }

    // Print out all candidates with no incoming edges (i.e. the "source" nodes)
    bool has_winner = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (incoming_edges[i] == 0)
        {
            printf("%s\n", candidates[i]);
            has_winner = true;
        }
    }

    // If no candidate had no incoming edges, there must be a tie.
    if (!has_winner)
    {
        printf("Tie\n");
    }
}