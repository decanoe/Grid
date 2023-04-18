#include "Class/Grid.h"
#include "Functions.h"
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


void WriteSolution(Grid& G, Solution& S, std::string filePath)
{
    std::ofstream file = std::ofstream(filePath);
    if (!file)
    {
        std::cout << "Writing is not allowed";
        return;
    }

    for (int x = 0; x < S.size; x++)
    {
        for (int y = 0; y < S.size; y++)
        {
            file << S.Access(x, y);
        }
        file << "\n";
    }

    file << computeScore(G, S);
}