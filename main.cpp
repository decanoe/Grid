#include <iostream>
#include <string>
#include "InputOutput.h"

int main()
{
    std::string inPath, outPath;
    std::cin >> inPath >> outPath;

    Grid G = ReadGrid(inPath);
}