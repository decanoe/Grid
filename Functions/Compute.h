#pragma once
#include "../Class/Grid.h"

bool adjacent(Solution S, int x, int y);

int adjacentPairCount(Solution S, int x, int y);

int queenPairCount(Solution S, int x, int y);

int computeScore(Grid G, Solution S);