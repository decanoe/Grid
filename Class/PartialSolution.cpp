#include "PartialSolution.h"
#include "../Functions/Compute.h"
#include "Grid.h"
#include <iostream>
#include <cmath>

PartialSolutionCell::PartialSolutionCell() {}
PartialSolutionCell::PartialSolutionCell(Grid* G, int x, int y)
{
    this->grid = G;
    this->xPos = x;
    this->yPos = y;

    this->scores = new float[5];
    this->collapsedColor = 'B';
}

// Premiers placements
void PartialSolutionCell::InitScores(int negative_positive_diff)
{
    //================= Red ==========================
    this->maxScore = -this->grid->Read(xPos, yPos);
    this->scores[0] = this->maxScore;

    //================= Green ========================
    this->scores[1] = grid->Read(xPos, yPos) + grid->Read(xPos, yPos - 1)
                      + grid->Read(xPos - 1, yPos) + grid->Read(xPos + 1, yPos) + grid->Read(xPos, yPos + 1);
    if (this->maxScore < this->scores[1])
        this->maxScore = this->scores[1];

    //================= Yellow =======================
    this->scores[2] = grid->Read(xPos, yPos);
    if (this->maxScore < this->scores[2])
        this->maxScore = this->scores[2];

    //================= Black ========================
    this->scores[3] = 2*(grid->Read(xPos, yPos) - 1);
    if (this->maxScore < this->scores[3])
        this->maxScore = this->scores[3];
    
    //================= Orange =======================
    this->scores[4] = 1 - (float)GetOrangeInWay() / (grid->size * grid->size + 2);
    if (this->maxScore < this->scores[4])
        this->maxScore = this->scores[4];
    
    
    RefreshMaxScore(negative_positive_diff);
}
int PartialSolutionCell::GetOrangeInWay()
{
    // on ajoute le nombre de cases sur les lignes et diagonales afin d'empecher le programme de poser un orange sur un endroit en bloquant d'autres
    int orangeInTheWay =  grid->size - 1 // horizontal
                        + grid->size - 1; // vertical
    for (int i = 1; i < grid->size; i++)
    {
        if (grid->IsPosInGrid(xPos + i, yPos + i))
                orangeInTheWay += 1;
        if (grid->IsPosInGrid(xPos + i, yPos - i))
                orangeInTheWay += 1;
        if (grid->IsPosInGrid(xPos - i, yPos - i))
                orangeInTheWay += 1;
        if (grid->IsPosInGrid(xPos - i, yPos + i))
                orangeInTheWay += 1;
    }
    return orangeInTheWay;
}

bool PartialSolutionCell::IsCollapsed()
{
    return this->collapsedColor != 'B';
}
float PartialSolutionCell::GetMaxScore()
{
    return this->maxScore;
}
int PartialSolutionCell::GetBestColor()
{
    int color = 0;
    for (int i = 1; i < 5; i++)
    {
        if (this->scores[i] > this->scores[color])
            color = i;
    }
    return color;
}
void PartialSolutionCell::RefreshMaxScore(int negative_positive_diff)
{
    this->maxScore = this->scores[0];
    if (this->maxScore < this->scores[1])
        this->maxScore = this->scores[1];
    if (this->maxScore < this->scores[2])
        this->maxScore = this->scores[2];
    if (this->maxScore < this->scores[3])
        this->maxScore = this->scores[3];
    if (this->maxScore < this->scores[4])
        this->maxScore = this->scores[4];
    
    
    int positive_negative_penality = 0;
    if (negative_positive_diff > 0)
    {
        if (this->grid->Read(xPos, yPos) < 0)
            positive_negative_penality = this->grid->penalty;
        else if (this->grid->Read(xPos, yPos) > 0)
            positive_negative_penality = -this->grid->penalty;
    }
    else if (negative_positive_diff == 0)
    {
        if (this->grid->Read(xPos, yPos) > 0)
            positive_negative_penality -= this->grid->penalty;
    }

    this->maxScore += positive_negative_penality;
}

void PartialSolutionCell::Collapse_Red(PartialSolution* Solution)
{
    this->collapsedColor = 'R';
    
    for (int x = 0; x < Solution->size; x++)
    for (int y = 0; y < Solution->size; y++)
    {
        if (!Solution->cells[x][y].IsCollapsed())
        {
            Solution->cells[x][y].scores[0] = -2048* std::abs(this->grid->penalty);
            Solution->cells[x][y].RefreshMaxScore(Solution->negative_positive_diff);
        }
    }
}
void PartialSolutionCell::Collapse_Green(PartialSolution* Solution)
{
    this->collapsedColor = 'V';
    
    for (int x = -1; x <= 1; x++)
    for (int y = -1; y <= 1; y++)
    {
        if (!Solution->IsPosInGrid(xPos + x, yPos + y)) continue;

        if (!Solution->cells[xPos + x][yPos + y].IsCollapsed())
        {
            Solution->cells[xPos + x][yPos + y].scores[1] -= this->grid->penalty;
            Solution->cells[xPos + x][yPos + y].RefreshMaxScore(Solution->negative_positive_diff);
        }
    }
}
void PartialSolutionCell::Collapse_Yellow(PartialSolution* Solution)
{
    this->collapsedColor = 'J';

    for (int x = -1; x <= 1; x++)
    for (int y = -1; y <= 1; y++)
    {
        if (!Solution->IsPosInGrid(xPos + x, yPos + y)) continue;

        if (!Solution->cells[xPos + x][yPos + y].IsCollapsed())
        {
            Solution->cells[xPos + x][yPos + y].scores[2] = this->grid->Read(xPos + x, yPos + y) + Solution->penalty / 2;
            Solution->cells[xPos + x][yPos + y].RefreshMaxScore(Solution->negative_positive_diff);
        }
    }
}
void PartialSolutionCell::Collapse_Black(PartialSolution* Solution)
{
    this->collapsedColor = 'N';
    Solution->blackCount += 1;

    if (Solution->blackCount == Solution->size)
    {
        int blackSum = 0; // the sum of all black already placed on the grid
        for (int x = 0; x < Solution->size; x++)
        for (int y = 0; y < Solution->size; y++)
        {
            if (Solution->cells[x][y].collapsedColor == 'N')
            {
                blackSum += grid->Read(x, y) - 1;
            }
        }

        for (int x = 0; x < Solution->size; x++)
        for (int y = 0; y < Solution->size; y++)
        {
            if (!Solution->cells[x][y].IsCollapsed())
            {
                Solution->cells[x][y].scores[3] /= 2;
                Solution->cells[x][y].scores[3] -= blackSum;
                Solution->cells[x][y].RefreshMaxScore(Solution->negative_positive_diff);
            }
        }
    }
}
void PartialSolutionCell::Collapse_Orange(PartialSolution* Solution)
{
    this->collapsedColor = 'O';

    for (int i = 0; i < Solution->size; i++)
    {
        // vertical
        if (!Solution->cells[xPos][i].IsCollapsed())
        {
            Solution->cells[xPos][i].scores[4] -= this->grid->penalty;
            Solution->cells[xPos][i].RefreshMaxScore(Solution->negative_positive_diff);
        }

        // horizontal
        if (!Solution->cells[i][yPos].IsCollapsed())
        {
            Solution->cells[i][yPos].scores[4] -= this->grid->penalty;
            Solution->cells[i][yPos].RefreshMaxScore(Solution->negative_positive_diff);
        }

        // Diagonal up right
        if (Solution->IsPosInGrid(xPos + i, yPos + i))
        {
            if (!Solution->cells[xPos + i][yPos + i].IsCollapsed())
            {
                Solution->cells[xPos + i][yPos + i].scores[4] -= this->grid->penalty;
                Solution->cells[xPos + i][yPos + i].RefreshMaxScore(Solution->negative_positive_diff);
            }
        }
        // Diagonal up left
        if (Solution->IsPosInGrid(xPos - i, yPos + i))
        {
            if (!Solution->cells[xPos - i][yPos + i].IsCollapsed())
            {
                Solution->cells[xPos - i][yPos + i].scores[4] -= this->grid->penalty;
                Solution->cells[xPos - i][yPos + i].RefreshMaxScore(Solution->negative_positive_diff);
            }
        }
        // Diagonal down right
        if (Solution->IsPosInGrid(xPos + i, yPos - i))
        {
            if (!Solution->cells[xPos + i][yPos - i].IsCollapsed())
            {
                Solution->cells[xPos + i][yPos - i].scores[4] -= this->grid->penalty;
                Solution->cells[xPos + i][yPos - i].RefreshMaxScore(Solution->negative_positive_diff);
            }
        }
        // Diagonal down left
        if (Solution->IsPosInGrid(xPos - i, yPos - i))
        {
            if (!Solution->cells[xPos - i][yPos - i].IsCollapsed())
            {
                Solution->cells[xPos - i][yPos - i].scores[4] -= this->grid->penalty;
                Solution->cells[xPos - i][yPos - i].RefreshMaxScore(Solution->negative_positive_diff);
            }
        }
    }
}
void PartialSolutionCell::ChangeNearbyOrange(PartialSolution* Solution)
{
    for (int i = 0; i < Solution->size; i++)
    {
        // vertical
        if (!Solution->cells[xPos][i].IsCollapsed())
        {
            Solution->cells[xPos][i].scores[4] += 1. / (grid->size * grid->size + 2);
            Solution->cells[xPos][i].RefreshMaxScore(Solution->negative_positive_diff);
        }

        // horizontal
        if (!Solution->cells[i][yPos].IsCollapsed())
        {
            Solution->cells[i][yPos].scores[4] += 1. / (grid->size * grid->size + 2);
            Solution->cells[i][yPos].RefreshMaxScore(Solution->negative_positive_diff);
        }

        // Diagonal up right
        if (Solution->IsPosInGrid(xPos + i, yPos + i))
        {
            if (!Solution->cells[xPos + i][yPos + i].IsCollapsed())
            {
                Solution->cells[xPos + i][yPos + i].scores[4] += 1. / (grid->size * grid->size + 2);
                Solution->cells[xPos + i][yPos + i].RefreshMaxScore(Solution->negative_positive_diff);
            }
        }
        // Diagonal up left
        if (Solution->IsPosInGrid(xPos - i, yPos + i))
        {
            if (!Solution->cells[xPos - i][yPos + i].IsCollapsed())
            {
                Solution->cells[xPos - i][yPos + i].scores[4] += 1. / (grid->size * grid->size + 2);
                Solution->cells[xPos - i][yPos + i].RefreshMaxScore(Solution->negative_positive_diff);
            }
        }
        // Diagonal down right
        if (Solution->IsPosInGrid(xPos + i, yPos - i))
        {
            if (!Solution->cells[xPos + i][yPos - i].IsCollapsed())
            {
                Solution->cells[xPos + i][yPos - i].scores[4] += 1. / (grid->size * grid->size + 2);
                Solution->cells[xPos + i][yPos - i].RefreshMaxScore(Solution->negative_positive_diff);
            }
        }
        // Diagonal down left
        if (Solution->IsPosInGrid(xPos - i, yPos - i))
        {
            if (!Solution->cells[xPos - i][yPos - i].IsCollapsed())
            {
                Solution->cells[xPos - i][yPos - i].scores[4] += 1. / (grid->size * grid->size + 2);
                Solution->cells[xPos - i][yPos - i].RefreshMaxScore(Solution->negative_positive_diff);
            }
        }
    }

}

void PartialSolutionCell::Collapse(PartialSolution* Solution)
{
    if (this->grid->Read(this->xPos, this->yPos) > 0)
        Solution->negative_positive_diff += 1;
    else if (this->grid->Read(this->xPos, this->yPos) < 0)
        Solution->negative_positive_diff -= 1;
    
    if (Solution->negative_positive_diff > -2)
    {
        // refresh to count blue count change
        for (int x = 0; x < Solution->size; x++)
        for (int y = 0; y < Solution->size; y++)
        {
            if (!Solution->cells[x][y].IsCollapsed())
                Solution->cells[x][y].RefreshMaxScore(Solution->negative_positive_diff);
        }
    }
    
    switch (GetBestColor())
    {
    case 0:
        Collapse_Red(Solution);
        break;

    case 1:
        Collapse_Green(Solution);
        break;

    case 2:
        Collapse_Yellow(Solution);
        break;

    case 3:
        Collapse_Black(Solution);
        break;

    case 4:
        Collapse_Orange(Solution);
        break;
    
    default:
        break;
    }

    ChangeNearbyOrange(Solution);

    delete[] scores;
}



// Grille
bool PartialSolution::IsPosInGrid(int x, int y)
{
    return x >= 0 && y >= 0 && x < this->size && y < this->size;
}
int PartialSolution::ComputeBlue()
{
    if (this->negative_positive_diff <= 0) return 0;
    return -this->negative_positive_diff * this->penalty;
}

PartialSolution::PartialSolution(Grid* G)
{
    this->size = G->size;
    this->penalty = G->penalty;
    this->negative_positive_diff = 0;
    this->blackCount = 0;

    this->cells = new PartialSolutionCell*[G->size];
    for (int i = 0; i < G->size; ++i) 
    {
        this->cells[i] = new PartialSolutionCell[G->size];
        for (int j = 0; j < G->size; ++j)
        {
            this->cells[i][j] = PartialSolutionCell(G, i, j);

            if (G->Read(i, j) > 0) negative_positive_diff -= 1;
            else if (G->Read(i, j) < 0) negative_positive_diff += 1;
        }
    }

    for (int i = 0; i < G->size; ++i)
    for (int j = 0; j < G->size; ++j)
    {
        this->cells[i][j].InitScores(negative_positive_diff);
    }
}

int randomIndex(int length)
{
    float x = std::rand() % length;
    x /= (float)length;
    x *= x;
    return (int)roundf(x * length);
}
float PartialSolution::GetBestCell(int& x, int& y)
{
    int diffNb = this->size;
    int* xList = new int[diffNb];
    int* yList = new int[diffNb];
    float* maxList = new float[diffNb];
    for (int i = 0; i < diffNb; i++)
    {
        xList[i] = -1;
    }
    int nbValues = 0;

    for (int i = 0; i < this->size; ++i)
    for (int j = 0; j < this->size; ++j)
    {
        if (this->cells[i][j].IsCollapsed()) continue;
        float score = this->cells[i][j].GetMaxScore();

        for (int index = 0; index < this->size; index++)
        {
            if (xList[index] == -1)
            {
                xList[index] = i;
                yList[index] = j;
                maxList[index] = score;
                nbValues += 1;
                break;
            }
            if (score > maxList[index])
            {
                xList[index] = i;
                yList[index] = j;

                float temp = maxList[index];
                maxList[index] = score;
                score = temp;
            }
        }
    }
    
    int chosenIndex = randomIndex(nbValues);
    x = xList[chosenIndex];
    y = yList[chosenIndex];
    float max = maxList[chosenIndex];

    delete[] xList;
    delete[] yList;
    delete[] maxList;

    return max;
}
Solution PartialSolution::Solve()
{
    int x, y;

    Solution S = Solution(this->size);
    Solution Scopy = Solution(this->size);
    for (int i = 0; i < this->size; ++i)
    for (int j = 0; j < this->size; ++j)
    {
        S.Access(i, j) = this->cells[i][j].collapsedColor;
        Scopy.Access(i, j) = this->cells[i][j].collapsedColor;
    }
    
    for (int i = 0; i < this->size*this->size; ++i)
    {
        if (this->GetBestCell(x, y) >= this->ComputeBlue())
        {
            this->cells[x][y].Collapse(this);
            Scopy.Access(x, y) = this->cells[x][y].collapsedColor;
            
            if (computeScore(*this->cells[x][y].grid, Scopy) > computeScore(*this->cells[x][y].grid, S))
            {
                for (int i = 0; i < this->size; ++i)
                for (int j = 0; j < this->size; ++j)
                {
                    S.Access(i, j) = this->cells[i][j].collapsedColor;
                }
            }
        }
        else break;
        // this->Print();
    }

    // testing for red
    int bestPosX = -1;
    int bestPosY = -1;
    for (int i = 0; i < this->size; ++i)
    for (int j = 0; j < this->size; ++j)
    {
        if (S.Read(i, j) == 'R')
            return S;
        
        if (bestPosX == -1)
        {
            bestPosX = i;
            bestPosY = j;
            continue;
        }
        if (S.Read(i, j) < S.Read(bestPosX, bestPosY))
        {
            bestPosX = i;
            bestPosY = j;
        }
    }

    S.Access(bestPosX, bestPosY) = 'R';
    return S;
}

// show the Solution in the terminal
void PartialSolution::Print()
{
    for (int x = 0; x < this->size; x++)
    {
        for (int y = 0; y < this->size; y++)
        {
            if (this->cells[x][y].IsCollapsed())
            {
                int value = this->cells[x][y].grid->Read(x, y);
                switch (this->cells[x][y].collapsedColor)
                {
                case 'R': // red
                    std::cout << "\033[41m" << value << "(R)\t\033[0m";
                    break;
                case 'V': // green
                    std::cout << "\033[42m" << value << "(V)\t\033[0m";
                    break;
                case 'J': // yellow
                    std::cout << "\033[43m" << value << "(J)\t\033[0m";
                    break;
                case 'N': // black
                    std::cout << "\033[30;47m" << value << "(N)\t\033[0m";
                    break;
                case 'O': // orange
                    std::cout << "\033[45;33m" << value << "(O)\t\033[0m";
                    break;
                
                default:
                    break;
                }
            }
            else
            {
                float value = this->cells[x][y].GetMaxScore();
                value = std::roundf(value * 1000) / 1000.0;
                // std::cout << "\033[32m" << this->cells[x][y].scores[1] << "\033[0m\t";
                // continue;
                switch (this->cells[x][y].GetBestColor())
                {
                case 0: // red
                    std::cout << "\033[31m" << value << "\033[0m\t";
                    break;
                case 1: // green
                    std::cout << "\033[32m" << value << "\033[0m\t";
                    break;
                case 2: // yellow
                    std::cout << "\033[33m" << value << "\033[0m\t";
                    break;
                case 3: // black
                    std::cout << "\033[30m" << value << "\033[0m\t";
                    break;
                case 4: // orange
                    std::cout << "\033[35m" << value << "\033[0m\t";
                    break;
                
                default:
                    break;
                }
            }
        }
        std::cout << "\n";
    }
}

void PartialSolutionCell::Delete()
{
    delete[] this->scores;
}
void PartialSolution::Delete()
{
    for (int x = 0; x < this->size; x++)
    {
        for (int y = 0; y < this->size; y++)
        {
            if (!this->cells[x][y].IsCollapsed())
                this->cells[x][y].Delete();
        }
        delete[] this->cells[x];
    }
    delete[] this->cells;
}