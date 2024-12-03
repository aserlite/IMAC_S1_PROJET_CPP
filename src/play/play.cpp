#include "play.hpp"
#include <iostream>
#include <vector>

Play::Play(int boardSize) : board(boardSize), currentPlayer('X') {}

void Play::startSoloGame()
{
    bool gameRunning = true;
    srand (time(NULL));
    char first_player = rand() % 2 ? 'X' : 'O';
    if (first_player == 'X') {
        std::cout << "Vous commencez la partie\n";    
    } else {
        std::cout << "L'IA commence la partie\n";    
    }
    while (gameRunning)
    {
        board.displayBoard();
        int row, col;
        if (currentPlayer == first_player) {
            std::cout << "Joueur " << currentPlayer << ", entrez votre coup (ligne colonne) : ";
            std::cin >> row >> col;

            if (board.updateCell(row, col, currentPlayer))
            {
                if (checkWin())
                {
                    board.displayBoard();
                    std::cout << "Le joueur " << currentPlayer << " a gagné !\n";
                    gameRunning = false;
                }
                else if (checkDraw())
                {
                    board.displayBoard();
                    std::cout << "Match nul !\n";
                    gameRunning = false;
                }
                else
                {
                    switchPlayer();
                }
            }
            else
            {
                std::cout << "Coup invalide, réessayez.\n";
            }
        } else {
            std::vector<std::vector<char>> boardState = board.getState();
            std::pair<int, int> move = ai.calculateMove(boardState, currentPlayer);

            if (move.first != -1 && move.second != -1) {
                board.updateCell(move.first, move.second, currentPlayer);
                std::cout << "IA a joué en (" << move.first << ", " << move.second << ")\n";

                if (checkWin())
                {
                    board.displayBoard();
                    std::cout << "L'IA a gagné !\n";
                    gameRunning = false;
                }
                else if (checkDraw())
                {
                    board.displayBoard();
                    std::cout << "Match nul !\n";
                    gameRunning = false;
                }
                else
                {
                    switchPlayer();
                }
            } else {
                std::cout << "L'IA n'a pas trouvé de coup valide (bug).\n";
                gameRunning = false;
            }
        }
    }
}

void Play::startDuoGame()
{
    bool gameRunning = true;

    while (gameRunning)
    {
        board.displayBoard();
        int row, col;
        std::cout << "Joueur " << currentPlayer << ", entrez votre coup (ligne colonne) : ";
        std::cin >> row >> col;

        if (board.updateCell(row, col, currentPlayer))
        {
            if (checkWin())
            {
                board.displayBoard();
                std::cout << "Le joueur " << currentPlayer << " a gagné !\n";
                gameRunning = false;
            }
            else if (checkDraw())
            {
                board.displayBoard();
                std::cout << "Match nul !\n";
                gameRunning = false;
            }
            else
            {
                switchPlayer();
            }
        }
        else
        {
            std::cout << "Coup invalide, réessayez.\n";
        }
    }
}

void Play::switchPlayer()
{
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool Play::checkWin() const
{
    for (int i = 0; i < 3; i++)
    {
        if (board.getCell(i, 0) == board.getCell(i, 1) && board.getCell(i, 1) == board.getCell(i, 2) && board.getCell(i, 0) != ' ')
        {
            return true;
        }
        if (board.getCell(0, i) == board.getCell(1, i) && board.getCell(1, i) == board.getCell(2, i) && board.getCell(0, i) != ' ')
        {
            return true;
        }
    }
    if (board.getCell(0, 0) == board.getCell(1, 1) && board.getCell(1, 1) == board.getCell(2, 2) && board.getCell(0, 0) != ' ')
    {
        return true;
    }
    if (board.getCell(2, 0) == board.getCell(1, 1) && board.getCell(1, 1) == board.getCell(0, 2) && board.getCell(2, 0) != ' ')
    {
        return true;
    }
    return false;
}

bool Play::checkDraw() const
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (board.getCell(i, j) == ' ')
            {
                return false;
            }
        }
    }

    return true;
}

Play::~Play()
{
}
