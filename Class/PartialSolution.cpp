#include "PartialSolution.h"
#include "Grid.h"

PartialSolution::PartialSolution(Grid G)
{
    this->cells = new PartialSolutionCell*[G.size];
    for (int i = 0; i < G.size; ++i) 
    {
        this->cells[i] = new PartialSolutionCell[G.size];
        for (int j = 0; j < G.size; ++j)
        {
            this->cells[i][j] = PartialSolutionCell(&G, i, j);
            this->cells[i][j].InitScores();
        }
    }
}

void PartialSolution::GetBestCell(int& x, int& y)
{
    int x = -1;
    int y = -1;
    int max = 0;

    for (int i = 0; i < this->size; ++i)
    for (int j = 0; j < this->size; ++j)
    {
        if (this->cells[i][j].IsCollapsed()) continue;
        if ((x == -1) or (this->cells[i][j].GetMaxScore() > max))
        {
            x = i;
            y = j;
            max = this->cells[x][y].GetMaxScore();
        }
    }
}

Solution PartialSolution::Solve()
{
    int x, y;

    for (int i = 0; i < this->size; ++i)
    for (int j = 0; j < this->size; ++j)
    {
        this->GetBestCell(x, y);
        this->cells[x][y].Collapse(this);
    }
}