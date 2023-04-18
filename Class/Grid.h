#pragma once
#include <string>

class Grid
{
private:
    int* values;
public:
    int size;
    int penalty;

    Grid(int size, int penalty);
    int Access(int x, int y) const;
    int& Access(int x, int y);
};

class Solution
{
private:
    std::string* color;
public:
    int size;

    Solution(int size);
    std::string Access(int x, int y);
};