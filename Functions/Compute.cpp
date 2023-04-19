#include "Compute.h"
#include "../Class/Grid.h"
#include <iostream>

/*Returns true if the same color is on a surrounding cell*/
bool adjacent(Solution S, int x, int y)
{
    if (S.Read(x, y) == S.Read(x - 1, y - 1)) return true;
    if (S.Read(x, y) == S.Read(x - 1, y)) return true;
    if (S.Read(x, y) == S.Read(x - 1, y + 1)) return true;
    if (S.Read(x, y) == S.Read(x, y - 1)) return true;
    if (S.Read(x, y) == S.Read(x, y + 1)) return true;
    if (S.Read(x, y) == S.Read(x + 1, y - 1)) return true;
    if (S.Read(x, y) == S.Read(x + 1, y)) return true;
    if (S.Read(x, y) == S.Read(x + 1, y + 1)) return true;
    
    return false;
}

/*Returns the number of pairs of the same color on surrounding cells (without diagonals)*/
int adjacentPairCount(Solution S, int x, int y)
{
    int count = 0;

    // Four cases treated : top-right, right, bottom-right and bottom
    if (S.Read(x, y) == S.Read(x + 1, y - 1)) count += 1;
    if (S.Read(x, y) == S.Read(x + 1, y)) count += 1;
    if (S.Read(x, y) == S.Read(x + 1, y + 1)) count += 1;
    if (S.Read(x, y) == S.Read(x, y + 1)) count += 1;

    return count;
}

/*Returns the number of pairs of same color that are on the same line/diagonal*/
int queenPairCount(Solution S, int x, int y)
{
    int count = 0;
    int n = std::max(S.size - x, S.size - y);

    // Four cases treated : top-right, right, bottom-right and bottom
    for (int i = 1; i < n; ++i)
    {
        if (S.Read(x, y) == S.Read(x + i, y - i)) count += 1;
        if (S.Read(x, y) == S.Read(x + i, y)) count += 1;
        if (S.Read(x, y) == S.Read(x + i, y + i)) count += 1;
        if (S.Read(x, y) == S.Read(x, y + i)) count += 1;
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
            switch (S.Read(x, y))
            {
            case 'N':
                ++black_count;
                black_score += G.Read(x, y) - 1;
                break;
            case 'J':
                yellow_score += G.Read(x, y);
                if (!adjacent(S, x, y)) penalty_count += 1;
                break;
            case 'V':
                green_score += G.Read(x, y) + G.Read(x, y - 1)
                             + G.Read(x - 1, y) + G.Read(x + 1, y) + G.Read(x, y + 1);
                penalty_count += adjacentPairCount(S, x, y);
                break;
            case 'B':
                if (G.Read(x, y) < 0) blue_penalty += 1;
                else if (G.Read(x, y) > 0) blue_penalty -= 1;
                break;
            case 'O':
                penalty_count += queenPairCount(S, x, y);
                break;
            case 'R':
                red_score += -G.Read(x, y);
                break;
            
            default:
                std::cerr << "Incorrect color in solution at " << x <<  "," << y << std::endl;
                break;
            }
        }
    }

    //penalty if there are more negative blue cells than positive blue cells
    if (blue_penalty > 0) penalty_count += blue_penalty;

    //doubles black score if black_count <= grid size
    if (black_count <= G.size) black_score *= 2;

    return black_score + red_score + yellow_score + green_score
           - penalty_count*G.penalty;
}