#include <iostream>
#include <string>
#include "Grid.h"

Grid::Grid(int size, int penalty)
{
    this->values = new int[size * size];
    this->size = size;
    this->penalty = penalty;
}
/* Acces the value in the (x, y) cell of the grid */
int Grid::Read(int x, int y) const
{
    // return 0 if the requested value is outside of the grid
    if (x < 0 || y < 0 || x >= this->size || y >= this->size)
    {
        return 0;
    }
    
    return values[x + y * this->size];
}
int& Grid::Access(int x, int y)
{
    // return an error if the requested value is outside of the grid
    if (x < 0 || y < 0 || x >= this->size || y >= this->size)
    {
        std::cerr << "ERROR : value outside of the grid";
        return values[0];
    }
    
    return values[x + y * this->size];
}
// show the grid in the terminal
void Grid::Print()
{
    for (int x = 0; x < this->size; x++)
    {
        for (int y = 0; y < this->size; y++)
        {
            std::cout << this->Read(x, y) << "\t";
        }
        std::cout << "\n";
    }
}

// ======================================================================================================

Solution::Solution(int size)
{
    this->color = new std::string[size * size];
    this->size = size;
}
/* Acces the color in the (x, y) cell of the solution */
std::string Solution::Read(int x, int y) const
{
    // return an empty string if the requested color is outside of the solution
    if (x < 0 || y < 0 || x >= this->size || y >= this->size)
    {
        return "";
    }
    
    return color[x + y * this->size];
}
std::string& Solution::Access(int x, int y)
{
    // return an error if the requested value is outside of the grid
    if (x < 0 || y < 0 || x >= this->size || y >= this->size)
    {
        std::cerr << "ERROR : value outside of the solution";
        return this->color[0];
    }
    
    return this->color[x + y * this->size];
}
// show the Solution in the terminal
void Solution::Print()
{
    for (int x = 0; x < this->size; x++)
    {
        for (int y = 0; y < this->size; y++)
        {
            std::cout << this->Read(x, y) << "\t";
        }
        std::cout << "\n";
    }
}
