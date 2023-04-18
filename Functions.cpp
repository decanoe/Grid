#include "Functions.h"
#include "Class/Grid.h"

/*Returns true if the same color is on a surrounding cell*/
bool adjacent(Solution S, int x, int y)
{
    if (S.Read(x, y) == S.Read(x - 1, y - 1) && (S.Read(x - 1, y - 1) != "")) return true;
    if (S.Read(x, y) == S.Read(x - 1, y) && (S.Read(x - 1, y) != "")) return true;
    if (S.Read(x, y) == S.Read(x - 1, y + 1) && (S.Read(x - 1, y + 1) != "")) return true;
    if (S.Read(x, y) == S.Read(x, y - 1) && (S.Read(x, y - 1) != "")) return true;
    if (S.Read(x, y) == S.Read(x, y + 1) && (S.Read(x, y + 1) != "")) return true;
    if (S.Read(x, y) == S.Read(x + 1, y - 1) && (S.Read(x + 1, y - 1) != "")) return true;
    if (S.Read(x, y) == S.Read(x + 1, y) && (S.Read(x + 1, y) != "")) return true;
    if (S.Read(x, y) == S.Read(x + 1, y + 1) && (S.Read(x + 1, y + 1) != "")) return true;
    
    return false;
}

/*Returns the number of pairs of the same color on surrounding cells (without diagonals)*/
int adjacentPairCount(Solution S, int x, int y)
{
    int count = 0;

    // Four cases treated : top-right, right, bottom-right and bottom
    if (S.Read(x, y) == S.Read(x + 1, y - 1) && (S.Read(x - 1, y + 1) != "")) count += 1;
    if (S.Read(x, y) == S.Read(x + 1, y) && (S.Read(x, y + 1) != "")) count += 1;
    if (S.Read(x, y) == S.Read(x + 1, y + 1) && (S.Read(x + 1, y + 1) != "")) count += 1;
    if (S.Read(x, y) == S.Read(x, y + 1) && (S.Read(x + 1, y) != "")) count += 1;

    return count;
}

/*Returns the number of pairs of same color that are on the same line/diagonal*/
int queenPairCount(Solution S, int x, int y)
{
    int count = 0;
    int i = 1;

    // Four cases treated : top-right, right, bottom-right and bottom
    while (S.Read(x + i, y - i) != "")
    {
        if (S.Read(x, y) == S.Read(x + i, y - i)) count += 1;
        i++;
    };

    i = 1;

    while (S.Read(x + i, y) != "")
    {
        if (S.Read(x, y) == S.Read(x + i, y)) count += 1;
        i++;
    }

    i = 1;

    while (S.Read(x + i, y + i) != "")
    {
        if (S.Read(x, y) == S.Read(x + i, y + i)) count += 1;
        i++;
    }

    i = 1;

    while (S.Read(x, y + i) != "")
    {
        if (S.Read(x, y) == S.Read(x, y + i)) count += 1;
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

    int blue_penalty = 0;

    for (int x = 0; x < G.size; ++x)
    {
        for (int y = 0; y < G.size; ++y)
        {
            if (S.Read(x, y) == "N") 
            {
                ++black_count;
                black_score += G.Read(x, y) - 1;
            }
            else if (S.Read(x, y) == "J")
            {
                yellow_score += G.Read(x, y);
                if (!adjacent(S, x, y)) penalty_count += 1;
            }
            else if (S.Read(x, y) == "V")
            {
                green_score += G.Read(x, y) + G.Read(x, y - 1)
                             + G.Read(x - 1, y) + G.Read(x + 1, y) + G.Read(x, y + 1);
                penalty_count += adjacentPairCount(S, x, y);
            }
            else if (S.Read(x, y) == "B")
            {
                if (G.Read(x, y) < 0) blue_penalty += 1;
                else if (G.Read(x, y) > 0) blue_penalty -= 1;
            }
            else if (S.Read(x, y) == "O") penalty_count += queenPairCount(S, x, y);
            else if (S.Read(x,y) == "R") red_score += -G.Read(x, y);
        }
    }

    //penalty if there are more negative blue cells than positive blue cells
    if (blue_penalty > 0) penalty_count += blue_penalty;

    //doubles black score if black_count <= grid size
    if (black_count <= G.size) black_score *= 2;

    return black_score + red_score + yellow_score + green_score
           - penalty_count*G.penalty;
}