#include <iostream>
#include <string>
#include "Functions/InputOutput.h"
#include "Functions/Compute.h"
#include "Class/PartialSolution.h"

int main()
{
    // Grid G = ReadGrid("./test_grids/probleme_12_a.txt");
    Grid G = ReadGrid("./test_grids/grid_exemple.txt");
    // G.Print();
    // std::cout << "\n";

    // Solution S = ReadSolution("./test_grids/solve_exemple.txt");
    // S.Print();

    // std::cout << computeScore(G, S);
    Solution best = Solution(0);
    int best_score = 0;
    int nb = 0;
    for (int i = 0; i < 128*128; i++)
    {
        PartialSolution PS = PartialSolution(&G);
        Solution S = PS.Solve();

        int score = computeScore(G, S);
        if (best_score < score)
        {
            best_score = score;
            nb = 1;
            best = S;
            std::cout << score << "\n";
        }
        else if (score == best_score)
            nb += 1;

        PS.Delete();
    }

    std::cout << "best grid :\n";
    best.Print();
    std::cout << "\nscore : " << best_score << " (nb of possibility found : " << nb << ")";

    return 0;
}