#include "Class/Grid.h"
#include <string>

Grid ReadGrid(std::string filePath);
void WriteSolution(Grid& G, Solution& S, std::string filePath);