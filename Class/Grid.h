#pragma once

class Grid
{
private:
    int* values;
public:
    unsigned int size;
    unsigned int penalty;

    Grid(int size, int penalty);
    int Access(int x, int y);
};

class Solution
{
private:
    int* color;
public:
    unsigned int size;

    Solution(int size);
    int Access(int x, int y);
};