#include <iostream>
#include <string>
#include "InputOutput.h"
#include "Functions.h"

int main()
{
    std::string Path;
    std::cin >> Path;

    Grid G = ReadGrid(Path);
    G.Print();

    std::cin >> Path;
    Solution S = ReadSolution(Path);
    S.Print();

    std::cout << computeScore(G, S);

    return 0;
}