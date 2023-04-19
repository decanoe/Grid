#include "PartialSolution.h"
#include "Grid.h"

void PartialSolutionCell::InitScores()
{
    //================= Red ==========================
    this->maxScore = -this->grid->Read(x, y);
    this->scores[0] = this->maxScore;

    //================= Green ========================
    this->scores[1] = grid->Read(x, y) + grid->Read(x, y - 1)
                      + grid->Read(x - 1, y) + grid->Read(x + 1, y) + grid->Read(x, y + 1);
    if (this->maxScore < this->scores[1])
        this->maxScore = this->scores[1];

    //================= Yellow =======================
    this->scores[2] = grid->Read(x, y);
    if (this->maxScore < this->scores[2])
        this->maxScore = this->scores[2];

    //================= Yellow =======================
    this->scores[2] = grid->Read(x, y);
    if (this->maxScore < this->scores[2])
        this->maxScore = this->scores[2];
        
    // case 'N':
    //     ++black_count;
    //     black_score += G.Read(x, y) - 1;
    //     break;
    // case 'J':
    //     yellow_score += G.Read(x, y);
    //     if (!adjacent(S, x, y)) penalty_count += 1;
    //     break;
    // case 'V':
    //     green_score += G.Read(x, y) + G.Read(x, y - 1)
    //                     + G.Read(x - 1, y) + G.Read(x + 1, y) + G.Read(x, y + 1);
    //     penalty_count += adjacentPairCount(S, x, y);
    //     break;
    // case 'B':
    //     if (G.Read(x, y) < 0) blue_penalty += 1;
    //     else if (G.Read(x, y) > 0) blue_penalty -= 1;
    //     break;
    // case 'O':
    //     penalty_count += queenPairCount(S, x, y);
    //     break;
    // case 'R':
    //     red_score += -G.Read(x, y);
    //     break;
}

PartialSolutionCell::~PartialSolutionCell()
{
    
}

PartialSolutionCell::PartialSolutionCell(Grid* G, int x, int y)
{
    this->grid = G;
    this->x = x;
    this->y = y;

    this->scores = new int[5];
    this->collapsedColor = 'e';
}

bool PartialSolutionCell::IsCollapsed()
{
    return this->collapsedColor == 'e';
}
int PartialSolutionCell::GetMaxScore()
{
    return this->maxScore;
}
void PartialSolutionCell::Collapse()
{
    int color = 0;
    for (int i = 1; i < 5; i++)
    {
        if (this->scores[i] > this->scores[color])
            color = i;
    }
    
    switch (color)
    {
    case 0:
        this->collapsedColor = 'R';
        break;
    case 1:
        this->collapsedColor = 'V';
        break;
    case 2:
        this->collapsedColor = 'J';
        break;
    case 3:
        this->collapsedColor = 'N';
        break;
    case 4:
        this->collapsedColor = 'O';
        break;
    
    default:
        break;
    }
}
