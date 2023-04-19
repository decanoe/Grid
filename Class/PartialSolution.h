#pragma once
#include "Grid.h"

class PartialSolution;

class PartialSolutionCell
{
private:
    int* scores;
    int cellValue;
    int maxScore;
    char collapsedColor;
public:
    PartialSolutionCell();
    
    bool IsCollapsed();
    int GetMaxScore();
    void Collapse(PartialSolution Solution);
};

class PartialSolution
{
private:
    int size;
    PartialSolutionCell* cells;
public:
    PartialSolution(Grid G);

    void GetBestCell(int& x, int& y);
    Solution Solve();
};