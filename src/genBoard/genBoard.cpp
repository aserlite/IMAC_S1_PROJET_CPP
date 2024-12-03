#include "genBoard.hpp"
#include <iostream>
#include <iomanip>

GenBoard::GenBoard(int size) : size(size), grid(size, std::vector<char>(size, ' '))
{
}

void GenBoard::displayBoard() const
{
    for (const auto &row : grid)
    {
        for (const auto &cell : row)
        {
            std::cout << "|" << (cell == ' ' ? ' ' : cell);
        }
        std::cout << "|\n";
    }
}

bool GenBoard::updateCell(int row, int col, char player)
{
    if (isCellFree(row, col))
    {
        grid[row][col] = player;
        return true;
    }
    return false;
}

bool GenBoard::isCellFree(int row, int col) const
{
    return grid[row][col] == ' ';
}

char GenBoard::getCell(int row, int col) const
{
    return grid[row][col];
}

std::vector<std::vector<char>> GenBoard::getState() const
{
    return grid;
}

GenBoard::~GenBoard()
{
}
