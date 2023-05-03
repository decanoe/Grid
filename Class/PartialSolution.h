#pragma once
#include "Grid.h"

class PartialSolution;

class PartialSolutionCell
{
private:
    int xPos, yPos;

    float maxScore;
public:
    Grid* grid;
    float* scores;
    char collapsedColor;

    PartialSolutionCell(Grid* G, int x, int y);
    PartialSolutionCell();
    
    void InitScores(int negative_positive_diff);
    int GetOrangeInWay();
    void ChangeNearbyOrange(PartialSolution* Solution);
    void Delete();

    bool IsCollapsed();
    float GetMaxScore();
    int GetBestColor();
    void RefreshMaxScore(int negative_positive_diff);
    void Collapse(PartialSolution* Solution);

    void Collapse_Red(PartialSolution* Solution);
    void Collapse_Green(PartialSolution* Solution);
    void Collapse_Yellow(PartialSolution* Solution);
    void Collapse_Black(PartialSolution* Solution);
    void Collapse_Orange(PartialSolution* Solution);
};

class PartialSolution
{
private:
public:
    PartialSolutionCell** cells;
    int size;
    int penalty;
    int negative_positive_diff;
    int blackCount;
    PartialSolution(Grid* G);

    bool IsPosInGrid(int x, int y);
    int ComputeBlue();
    float GetBestCell(int& x, int& y);
    Solution Solve();

    void Print();
    void Delete();
};