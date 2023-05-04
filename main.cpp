#include <iostream>
#include <string>
#include "Functions/InputOutput.h"
#include "Functions/Compute.h"
#include "Class/PartialSolution.h"

int main()
{
    Grid G = ReadGrid("./test_grids/probleme_12_a.txt");
    // Grid G = ReadGrid("./test_grids/grid_exemple.txt");
    // G.Print();
    // std::cout << "\n";

    // Solution S = ReadSolution("./test_grids/solve_exemple.txt");
    // S.Print();

    // std::cout << computeScore(G, S);
    for (int i = 0; i < 128*8; i++)
    {
        PartialSolution PS = PartialSolution(&G);
        Solution S = PS.Solve();

        int score = computeScore(G, S);
        if (score >= 633)
        {
            // G.Print();
            S.Print();
            std::cout << score << "\n";
        }

        PS.Delete();
    }

    return 0;
}