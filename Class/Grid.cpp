#include "Grid.h"
#include <iostream>
#include <string>

Grid::Grid(int size, int penality)
{
    this->values = new int[size * size];
    this->size = size;
    this->penality = penality;
}
/* Acces the value in the (x, y) cell of the grid */
int Grid::Access(int x, int y)
{
    // return 0 if the requested value is outside of the grid
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
    this->color = new std::string[size * size];
    this->size = size;
}
/* Acces the color in the (x, y) cell of the solution */
std::string Solution::Access(int x, int y)
{
    // return an empty string if the requested color is outside of the solution
    if (x < 0 || y < 0 || x >= this->size || y >= this->size)
    {
        return "";
    }
    
    return color[x + y * this->size];
}