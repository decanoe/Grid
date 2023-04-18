#include "Functions.h"
#include "Class/Grid.h"

/*Returns true if the same color is on a surrounding cell*/
bool adjacent(Solution S, int x, int y)
{
    if (S.Access(x, y) == S.Access(x - 1, y - 1) and S.Access(x - 1, y - 1)) return true;
    if (S.Access(x, y) == S.Access(x - 1, y) and S.Access(x - 1, y)) return true;
    if (S.Access(x, y) == S.Access(x - 1, y + 1) and S.Access(x - 1, y + 1)) return true;
    if (S.Access(x, y) == S.Access(x, y - 1) and S.Access(x, y - 1)) return true;
    if (S.Access(x, y) == S.Access(x, y + 1) and S.Access(x, y + 1)) return true;
    if (S.Access(x, y) == S.Access(x + 1, y - 1) and S.Access(x + 1, y - 1)) return true;
    if (S.Access(x, y) == S.Access(x + 1, y) and S.Access(x + 1, y)) return true;
    if (S.Access(x, y) == S.Access(x + 1, y + 1) and S.Access(x + 1, y + 1)) return true;
    
    return false;
}

/*Returns the number of pairs of the same color on surrounding cells (without diagonals)*/
int adjacentPairCount(Solution S, int x, int y)
{
    int count = 0;

    // Four cases treated : top-right, right, bottom-right and bottom
    if (S.Access(x, y) == S.Access(x + 1, y - 1) and S.Access(x - 1, y + 1)) count += 1;
    if (S.Access(x, y) == S.Access(x + 1, y) and S.Access(x, y + 1)) count += 1;
    if (S.Access(x, y) == S.Access(x + 1, y + 1) and S.Access(x + 1, y + 1)) count += 1;
    if (S.Access(x, y) == S.Access(x, y + 1) and S.Access(x + 1, y)) count += 1;

    return count;
}

/*Returns the number of pairs of same color that are on the same line/diagonal*/
int queenPairCount(Solution S, int x, int y)
{
    int count = 0;
    int i = 1;

    // Four cases treated : top-right, right, bottom-right and bottom
    while (not(S.Access(x + i, y - i)))
    {
        if (S.Access(x, y) == S.Access(x + i, y - i)) count += 1;
        i++;
    };

    int i = 1;

    while (not(S.Access(x + i, y)))
    {
        if (S.Access(x, y) == S.Access(x + i, y)) count += 1;
        i++;
    }

    int i = 1;

    while (not(S.Access(x + i, y + i)))
    {
        if (S.Access(x, y) == S.Access(x + i, y + i)) count += 1;
        i++;
    }

    int i = 1;

    while (not(S.Access(x, y + i)))
    {
        if (S.Access(x, y) == S.Access(x, y + i)) count += 1;
        i++;
    }

    return count;
}

/*Computes the score consdering a grid and its solution*/
int computeScore(Grid G, Solution S)
{
    int penalty_count = 0;

    int black_count = 0;
    int black_score = 0;
    int yellow_score = 0;
    int green_score = 0;
    int red_score = 0;

    int yellow_penalty = 0;
    int green_penalty = 0;
    int blue_penalty = 0;
    int orange_penalty = 0;

    for (int x = 0; x < G.size; ++x)
    {
        for (int y = 0; y < G.size; ++y)
        {
            if (S.Access(x, y) == 'N') 
            {
                ++black_count;
                black_score += G.Access(x, y) - 1;
            }
            else if (S.Access(x, y) == 'J')
            {
                yellow_score += G.Access(x, y);
                if (not(adjacent(S, x, y))) yellow_penalty += 1;
            }
            else if (S.Access(x, y) == 'V')
            {
                green_score += G.Access(x, y) + G.Access(x, y - 1)
                             + G.Access(x - 1, y) + G.Access(x + 1, y) + G.Access(x, y + 1);
                green_penalty += adjacentPairCount(S, x, y);
            }
            else if (S.Access(x, y) == 'B')
            {
                if (G.Access(x, y) < 0) blue_penalty += 1;
                else if (G.Access(x, y) > 0) blue_penalty -= 1;
            }
            else if (S.Access(x, y) == 'O') orange_penalty += queenPairCount(S, x, y);
            else if (S.Access(x,y) == 'R') red_score += -G.Access(x, y);
        }
    }

    //penalty if there are more negative blue cells than positive blue cells
    if (blue_penalty > 0) penalty_count += blue_penalty;

    //doubles black score if black_count <= grid size
    if (black_count <= G.size) black_score *= 2;

    return black_score + red_score + yellow_score + green_score
           - (yellow_penalty + green_penalty + blue_penalty + orange_penalty)*G.penalty;
}