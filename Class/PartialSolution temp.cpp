#include "PartialSolution.h"
#include "Grid.h"

void InitScores();

PartialSolutionCell::PartialSolutionCell(Grid* G, int x, int y)
{
    this->grid = G;
    this->x = x;
    this->y = y;

    this->scores = new int[5];
    this->collapsedColor = 'e';
}

bool PartialSolutionCell::IsCollapsed()
{
    return this->collapsedColor == 'e';
}
int PartialSolutionCell::GetMaxScore()
{
    return this->maxScore;
}
void PartialSolutionCell::Collapse(PartialSolution Solution)
{
    int color = 0;
    for (int i = 1; i < 5; i++)
    {
        if (this->scores[i] > this->scores[color])
            color = i;
    }
    
    switch (color)
    {
    case 0:
        this->collapsedColor = 'R';
        break;
    case 1:
        this->collapsedColor = 'V';
        break;
    case 2:
        this->collapsedColor = 'J';
        break;
    case 3:
        this->collapsedColor = 'N';
        break;
    case 4:
        this->collapsedColor = 'O';
        break;
    
    default:
        break;
    }
}
