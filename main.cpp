#include <iostream>
#include <string>
#include "Functions/InputOutput.h"
#include "Functions/Compute.h"
#include "Class/PartialSolution.h"

int main()
{
    Grid G = ReadGrid("./test_grids/grid_exemple.txt");
    //Grid G = ReadGrid("./test_grids/grid_exemple.txt");
    G.Print();
    std::cout << "\n";

    // Solution S = ReadSolution("./test_grids/solve_exemple.txt");
    // S.Print();

    // std::cout << computeScore(G, S);

    PartialSolution PS = PartialSolution(G);
    Solution S = PS.Solve();
    G.Print();
    S.Print();
    std::cout << computeScore(G, S);

    return 0;
}