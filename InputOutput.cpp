#include "Class/Grid.h"
#include <iostream>
#include <fstream>
#include <string>

Grid ReadGrid(std::string filePath)
{
    std::ifstream file = std::ifstream(filePath);

    int size, penality;
    file >> size >> penality;
    Grid G(size, penality);

    for (int x = 0; x < size; x++)
    for (int y = 0; y < size; y++)
    {
        file >> G.Access(x, y);
    }

    return G;
}


void WriteSolution(const Solution& S, std::string filePath);