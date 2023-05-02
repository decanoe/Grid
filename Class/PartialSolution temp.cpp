#include "PartialSolution.h"
#include "Grid.h"
#include <iostream>

bool PartialSolution::IsPosInGrid(int x, int y)
{
    return x >= 0 && y >= 0 && x < this->size && y < this->size;
}
int PartialSolution::ComputeBlue()
{
    if (this->negative_positive_diff >= 0) return 0;
    return this->negative_positive_diff * this->penalty;
}

void PartialSolutionCell::InitScores()
{
    //================= Red ==========================
    this->maxScore = -this->grid->Read(xPos, yPos);
    this->scores[0] = this->maxScore;

    //================= Green ========================
    this->scores[1] = grid->Read(xPos, yPos) + grid->Read(xPos, yPos - 1)
                      + grid->Read(xPos - 1, yPos) + grid->Read(xPos + 1, yPos) + grid->Read(xPos, yPos + 1);
    if (this->maxScore < this->scores[1])
        this->maxScore = this->scores[1];

    //================= Yellow =======================
    this->scores[2] = grid->Read(xPos, yPos);
    if (this->maxScore < this->scores[2])
        this->maxScore = this->scores[2];

    //================= Black ========================
    this->scores[3] = 2*(grid->Read(xPos, yPos) - 1);
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
    this->xPos = x;
    this->yPos = y;

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

void PartialSolutionCell::Collapse_Red(PartialSolution* Solution)
{
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
}
void PartialSolutionCell::Collapse_Green(PartialSolution* Solution)
{
    this->collapsedColor = 'V';
    
    for (int x = -1; x <= 1; x++)
    for (int y = -1; y <= 1; y++)
    {
        if (!Solution->IsPosInGrid(xPos + x, yPos + y)) continue;

        if (!Solution->cells[xPos + x][yPos + y].IsCollapsed() && x != 0 && y != 0)
        {
            Solution->cells[xPos + x][yPos + y].scores[1] -= this->grid->penalty;
            Solution->cells[xPos + x][yPos + y].RefreshMaxScore();
        }
    }
}
void PartialSolutionCell::Collapse_Yellow(PartialSolution* Solution)
{
    this->collapsedColor = 'J';

    for (int x = -1; x <= 1; x++)
    for (int y = -1; y <= 1; y++)
    {
        if (!Solution->IsPosInGrid(xPos + x, yPos + y)) continue;

        if (!Solution->cells[xPos + x][yPos + y].IsCollapsed() && x != 0 && y != 0)
        {
            Solution->cells[xPos + x][yPos + y].scores[2] = this->grid->Read(xPos + x, yPos + y);
            Solution->cells[xPos + x][yPos + y].RefreshMaxScore();
        }
    }
}
void PartialSolutionCell::Collapse_Black(PartialSolution* Solution)
{
    this->collapsedColor = 'N';
    Solution->blackCount += 1;

    if (Solution->blackCount == Solution->size)
    {
        for (int x = 0; x < Solution->size; x++)
        for (int y = 0; y < Solution->size; y++)
        {
            if (!Solution->cells[x][y].IsCollapsed())
            {
                Solution->cells[x][y].scores[3] /= 2;
                Solution->cells[x][y].RefreshMaxScore();
            }
        }
    }
}
void PartialSolutionCell::Collapse_Orange(PartialSolution* Solution)
{
    this->collapsedColor = 'O';

}

void PartialSolutionCell::Collapse(PartialSolution* Solution)
{
    int color = 0;
    for (int i = 1; i < 5; i++)
    {
        if (this->scores[i] > this->scores[color])
            color = i;
    }

    Solution->negative_positive_diff += 
        (this->grid->Read(this->xPos, this->yPos) > 0) ? -1 :
        (this->grid->Read(this->xPos, this->yPos) < 0) ? 1 : 0;
    
    switch (color)
    {
    case 0:
        Collapse_Red(Solution);
        break;
    case 1:
        Collapse_Green(Solution);
        break;

    case 2:
        Collapse_Yellow(Solution);
        break;

    case 3:
        Collapse_Black(Solution);
        break;

    case 4:
        Collapse_Orange(Solution);
        break;
    
    default:
        break;
    }

    delete[] scores;
}
