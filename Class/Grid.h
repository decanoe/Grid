#pragma once

class Grid
{
private:
    int* values;
public:
    int size;
    int penalty;

    Grid(int size, int penalty);
    int Read(int x, int y) const;
    int& Access(int x, int y);
    void Print();
};

class Solution
{
private:
    char* color;
public:
    int size;

    Solution(int size);
    char Read(int x, int y) const;
    char& Access(int x, int y);
    void Print();
};