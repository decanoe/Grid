#pragma once

class Grid
{
private:
    int* values;
public:
    unsigned int size;
    unsigned int penality;

    Grid(int size, int penality);
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