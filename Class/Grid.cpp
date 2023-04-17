#include "Grid.h"
#include <iostream>

Grid::Grid(int size, int penalty)
{
    this->values = new int[size * size];
    this->size = size;
    this->penalty = penalty;
}
/* Acces the value in the (x, y) cell of the grid */
int Grid::Access(int x, int y)
{
    // throws an error if the requested value is outside of the grid
    if (x < 0 || y < 0 || x >= this->size || y >= this->size)
    {
        std::cerr << "ERROR : value outside of the grid";
        return 0;
    }
    
    return values[x + y * this->size];
}

// ======================================================================================================

Solution::Solution(int size)
{
    this->color = new int[size * size];
    this->size = size;
}
/* Acces the color in the (x, y) cell of the solution */
int Solution::Access(int x, int y)
{
    // throws an error if the requested color is outside of the solution
    if (x < 0 || y < 0 || x >= this->size || y >= this->size)
    {
        std::cerr << "ERROR : value outside of the grid";
        return 0;
    }
    
    return color[x + y * this->size];
}