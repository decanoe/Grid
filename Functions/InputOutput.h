#pragma once
#include "../Class/Grid.h"
#include <string>

Grid ReadGrid(std::string filePath);
Solution ReadSolution(std::string filePath);
void WriteSolution(Grid& G, Solution& S, std::string filePath);