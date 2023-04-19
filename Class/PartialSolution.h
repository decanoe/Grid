#pragma once

class PartialSolution;

class PartialSolutionCell
{
private:
    int* scores;
    int maxScore;
    char collapsedColor;
public:
    PartialSolutionCell(/* args */);
    
    bool IsCollapsed();
    int GetMaxScore();
    void Collapse(PartialSolution Solution);
};

class PartialSolution
{
private:
    PartialSolutionCell* cells;
public:
    PartialSolution(/* args */);

    void GetBestCell(int& x, int& y);
    void Solve();
};