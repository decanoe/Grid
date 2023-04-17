#include Functions.h



int adjacentCount(Solutions S, int x, int y)
{
    int count = 0;
    if (S(x, y) == S(x-1, y-1) and S.Acces(x, y)) count += 1;
}

int calcul(Grid V, Solutions S)
{
    int score = 0;

    int black_count = 0;
    int black_score = 0;

    int yellow_score = 0;

    for (int y = 0; y < V.size; ++y)
    {
        for (int x = 0; x < V.size; ++x)
        {
            if (S(x, y) == 'R') score += -V(x, y);
            else if (S(x, y) == 'N') 
            {
                ++black_count;
                black_score += V(x, y);
            }
            else if (S(x,y) == 'J')
            {
                yellow_score += V(x, y);
            }
        }
    }


    if (black_count <= V.size) black_score *= 2;
    score += black_score;

    return score
}