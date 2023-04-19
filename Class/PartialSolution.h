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
    void RefreshMaxScore();
    void Collapse(PartialSolution* Solution);
};

class PartialSolution
{
private:
public:
    PartialSolutionCell** cells;
    int size;
    PartialSolution(Grid G);

    void GetBestCell(int& x, int& y);
    Solution Solve();
};