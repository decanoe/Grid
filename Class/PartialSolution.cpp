#include "PartialSolution.h"
#include "Grid.h"

PartialSolution::PartialSolution(Grid G)
{
    this->size = G.size;
    this->penalty = G.penalty;
    this->negative_positive_diff = 0;
    this->blackCount = 0;

    this->cells = new PartialSolutionCell*[G.size];
    for (int i = 0; i < G.size; ++i) 
    {
        this->cells[i] = new PartialSolutionCell[G.size];
        for (int j = 0; j < G.size; ++j)
        {
            this->cells[i][j] = PartialSolutionCell(&G, i, j);
            this->cells[i][j].InitScores();
            if (G.Read(i, j) > 0) negative_positive_diff -= 1;
            else if (G.Read(i, j) < 0) negative_positive_diff += 1;
        }
    }
}

int PartialSolution::GetBestCell(int& x, int& y)
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

    return max;
}

Solution PartialSolution::Solve()
{
    int x, y;
    Solution S = Solution(this->size);

    for (int i = 0; i < this->size*this->size; ++i)
    {
        if (this->GetBestCell(x, y) > this->ComputeBlue()) 
            this->cells[x][y].Collapse(this);
        else break;
    }

    for (int i = 0; i < this->size; ++i)
    for (int j = 0; j < this->size; ++j)
        S.Access(i, j) = this->cells[i][j].collapsedColor;

    return S;
}