#pragma once
#include <string>

class Grid
{
private:
    int* values;
public:
    unsigned int size;
    unsigned int penalty;

    Grid(int size, int penalty);
    int Access(int x, int y) const;
    int& Access(int x, int y);
};

class Solution
{
private:
    std::string* color;
public:
    unsigned int size;

    Solution(int size);
    std::string Access(int x, int y);
};