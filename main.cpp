#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "Functions/InputOutput.h"
#include "Functions/Compute.h"
#include "Class/PartialSolution.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "ERROR : No input grid were provided (use -h for help)";
        return 0;
    }

    if (strcmp(argv[1], "-h") == 0)
    {
        std::cout <<
            "arguments :" << 
            "\n\t<file>  \t: the path to the file containing the grid" <<
            "\n\t-o <file>\t: give a file path on which write the result" <<
            "\n\t-t <duration>\t: give a time limit (in seconds) to the calculation (default is 60s)"<<
            "\n\t-s <seed>\t: give a seed to the search (integer). Set 0 to use time as a seed";
        return 0;
    }

    std::string inputPath = argv[1];
    std::string outputPath = "";
    int maxTime = 60;
    bool seedSet = false;

    for (int i = 2; i < argc; i += 2)
    {
        if (strcmp(argv[i], "-o") == 0)
        {
            if (outputPath != "")
            {
                std::cerr << "ERROR : -o was used twice, only one output path is supported";
                return 0;
            }
            if (i + 1 >= argc)
            {
                std::cerr << "ERROR : -o was used but no output path were provided after it";
                return 0;
            }
            outputPath = argv[i + 1];
        }
        if (strcmp(argv[i], "-t") == 0)
        {
            if (maxTime != 60)
            {
                std::cerr << "ERROR : -t was used twice, only one duration is supported";
                return 0;
            }
            if (i + 1 >= argc)
            {
                std::cerr << "ERROR : -t was used but no duration were provided after it";
                return 0;
            }
            maxTime = std::stoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-s") == 0)
        {
            if (seedSet)
            {
                std::cerr << "ERROR : -t was used twice, only one seed is supported";
                return 0;
            }
            if (i + 1 >= argc)
            {
                std::cerr << "ERROR : -t was used but no seed were provided after it";
                return 0;
            }

            if (strcmp(argv[i + 1], "0") == 0)
                std::srand(time(NULL));
            else
                std::srand(std::stoi(argv[i + 1]));
            seedSet = true;
        }
    }
    
    Grid G = ReadGrid(inputPath);

    Solution best = Solution(0);
    int best_score = 0;
    clock_t best_time = 0;

    clock_t startTime = clock();
    clock_t lastTime = 0;
    while(clock() - startTime + lastTime < maxTime * CLOCKS_PER_SEC - lastTime * 10)
    {
        clock_t t = clock();

        PartialSolution PS = PartialSolution(&G);
        Solution S = PS.Solve();

        int score = computeScore(G, S);
        if (best_score < score || best.size == 0)
        {
            best_time = clock() - startTime;
            best_score = score;
            best = S;
            std::cout << score << "\n";
        }

        PS.Delete();

        lastTime = clock() - t;
    }

    std::cout << "best grid (found in " << (float)best_time/CLOCKS_PER_SEC << "s) :\n";
    best.Print();
    std::cout << "\nscore : " << best_score << " (time spent : " << ((float)(clock() - startTime))/CLOCKS_PER_SEC << "s with prints)";

    if (outputPath != "")
        WriteSolution(G, best, outputPath);

    return 0;
}