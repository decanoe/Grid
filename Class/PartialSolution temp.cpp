#include "PartialSolution.h"
#include "Grid.h"
#include <iostream>

void PartialSolutionCell::InitScores()
{
    //================= Red ==========================
    this->maxScore = -this->grid->Read(x, y);
    this->scores[0] = this->maxScore;

    //================= Green ========================
    this->scores[1] = grid->Read(x, y) + grid->Read(x, y - 1)
                      + grid->Read(x - 1, y) + grid->Read(x + 1, y) + grid->Read(x, y + 1);
    if (this->maxScore < this->scores[1])
        this->maxScore = this->scores[1];

    //================= Yellow =======================
    this->scores[2] = grid->Read(x, y);
    if (this->maxScore < this->scores[2])
        this->maxScore = this->scores[2];

    //================= Black ========================
    this->scores[3] = 2*(grid->Read(x, y) - 1);
    if (this->maxScore < this->scores[3])
        this->maxScore = this->scores[3];
    
    //================= Orange =======================
    this->scores[3] = 0;
    if (this->maxScore < this->scores[4])
        this->maxScore = this->scores[4];
}

PartialSolutionCell::PartialSolutionCell() {}
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
    return this->collapsedColor != 'e';
}
int PartialSolutionCell::GetMaxScore()
{
    return this->maxScore;
}
void PartialSolutionCell::RefreshMaxScore()
{
    this->maxScore = this->scores[0];
    if (this->maxScore < this->scores[1])
        this->maxScore = this->scores[1];
    if (this->maxScore < this->scores[2])
        this->maxScore = this->scores[2];
    if (this->maxScore < this->scores[3])
        this->maxScore = this->scores[3];
    if (this->maxScore < this->scores[4])
        this->maxScore = this->scores[4];
}

void PartialSolutionCell::Collapse(PartialSolution* Solution)
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
        for (int x = 0; x < Solution->size; x++)
        for (int y = 0; y < Solution->size; y++)
        {
            if (!Solution->cells[x][y].IsCollapsed())
            {
                Solution->cells[x][y].scores[0] = -INT_MAX;
                Solution->cells[x][y].RefreshMaxScore();
            }
        }
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
