#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return  true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp[1];
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int pi = preferences[pairs[i].winner][pairs[i].loser]
                     - preferences[pairs[i].loser][pairs[i].winner];
            int pj = preferences[pairs[j].winner][pairs[j].loser]
                     - preferences[pairs[j].loser][pairs[j].winner];
            if (pi < pj)
            {
                temp[0] = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp[0];
            }
        }
    }
    return;
}

bool cycle(int winner, int loser)
{
    //base
    if (locked[loser][winner] == true)
    {
        return true;
    }

    for (int j = 0; j < candidate_count; j++)
    {
        //If the loser is a winner in an existing locked pair: Look at that pair
        if (locked[loser][j] == true)
        {
            // then see if winner beats those lost to loser to see if it cycles
            if (cycle(winner, j))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (cycle(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}


// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == false)
            {
                printf("%s\n", candidates[j]);
            }
        }
    }
    return;
}

/*
record_preferences:
If you find that a candidate is preferred over another for a specific voter,
then I think you would just increase the correct place in the preferences array by 1

First, notice the two-dimensional array preferences. The integer preferences[i][j] will represent
the number of voters who prefer candidate i over candidate j.

So if you have a voter that votes as [2, 1, 0] then the preferences matrix would be
0, 0, 0
1, 0, 0
1, 1, 0

If the next vote is then [0, 2, 1] then the preferences matrix would be
0, 1, 1
1, 0, 0
1, 2, 0

lock_pairs:
./tideman a b c d e f g h i < Tideman_test.txt
https://gist.github.com/nicknapoli82/2379634e87f24399ed1ed12c4c2e8c9a
https://gist.github.com/nicknapoli82/6c5a1706489e70342e9a0a635ae738c9
https://cs50.stackexchange.com/questions/40210/pset3-tideman-lock-pairs-help
*/