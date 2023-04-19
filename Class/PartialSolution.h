#pragma once
#include "Grid.h"

class PartialSolution;

class PartialSolutionCell
{
private:
    Grid* grid;
    int x, y;

    int* scores;
    int maxScore;
    char collapsedColor;
public:
    PartialSolutionCell(Grid* G, int x, int y);
    PartialSolutionCell();
    
    void InitScores();

    bool IsCollapsed();
    int GetMaxScore();
    void Collapse(PartialSolution& Solution);
};

class PartialSolution
{
private:
    int size;
    PartialSolutionCell** cells;
public:
    PartialSolution(Grid G);

    void GetBestCell(int& x, int& y);
    Solution Solve();
};