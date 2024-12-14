#include "play.hpp"
#include <iostream>
#include <vector>

Play::Play(int boardSize) : board(boardSize), currentPlayer('X'), gameRunning(false), firstPlayer('X') {}

void Play::startSoloGame()
{
    std::cout << "Entrez votre nom: ";
    std::cin >> player1Name;
    std::cout << "Choisissez votre symbole (X ou O): ";
    std::cin >> player1Symbol;

    while (player1Symbol != 'X' && player1Symbol != 'O') {
        std::cout << "Symbole invalide. Choisissez X ou O: ";
        std::cin >> player1Symbol;
    }

    player2Symbol = (player1Symbol == 'X') ? 'O' : 'X';
    player2Name = "IA";

    gameRunning = true;
    srand(time(NULL));
    firstPlayer = rand() % 2 ? player1Symbol : player2Symbol;
    currentPlayer = firstPlayer;

    std::cout << (firstPlayer == player1Symbol ? player1Name : player2Name)
              << " commence la partie.\n";

    while (gameRunning)
    {
        board.displayBoard();
        if (currentPlayer == player1Symbol)
        {
            int row, col;
            while (true) {
                std::cout << player1Name << " (" << currentPlayer << "), entrez votre coup (ligne colonne) : ";
                if (!(std::cin >> row >> col)) {
                    std::cout << "Entrée invalide. Veuillez entrer des nombres pour la ligne et la colonne.\n";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    continue;
                }

                if (row < 0 || row >= board.getSize() || col < 0 || col >= board.getSize()) {
                    std::cout << "Position hors des limites. Veuillez entrer des valeurs entre 0 et " 
                              << board.getSize() - 1 << ".\n";
                    continue;
                }

                if (!board.isCellFree(row, col)) {
                    std::cout << "La cellule est déjà occupée. Choisissez une autre position.\n";
                    continue;
                }

                if (board.updateCell(row, col, currentPlayer)) {
                    break;
                }
            }

            if (checkWin())
            {
                board.displayBoard();
                std::cout << player1Name << " (" << currentPlayer << ") a gagné !\n";
                gameRunning = false;
            }
            else if (checkDraw())
            {
                board.displayBoard();
                std::cout << "Match nul !\n";
                gameRunning = false;
            }
            else {
                switchPlayer();
            }
        }
        else
        {
            auto [aiRow, aiCol] = ai.calculateMove(board.getState(), player2Symbol);
            board.updateCell(aiRow, aiCol, player2Symbol);
            std::cout << "IA (" << player2Symbol << ") a joué en position (" 
                      << aiRow << ", " << aiCol << ").\n";

            if (checkWin())
            {
                board.displayBoard();
                std::cout << "IA (" << currentPlayer << ") a gagné !\n";
                gameRunning = false;
            }
            else if (checkDraw())
            {
                board.displayBoard();
                std::cout << "Match nul !\n";
                gameRunning = false;
            }
            else {
                switchPlayer();
            }
        }
    }
}

void Play::startDuoGame()
{
    std::cout << "Entrez le nom du joueur 1: ";
    std::cin >> player1Name;
    std::cout << "Choisissez un symbole (X ou O): ";
    std::cin >> player1Symbol;

    while (player1Symbol != 'X' && player1Symbol != 'O') {
        std::cout << "Symbole invalide. Choisissez X ou O: ";
        std::cin >> player1Symbol;
    }

    std::cout << "Entrez le nom du joueur 2: ";
    std::cin >> player2Name;
    player2Symbol = (player1Symbol == 'X') ? 'O' : 'X';
    std::cout << "Le joueur 2 aura automatiquement le symbole: " << player2Symbol << std::endl;

    currentPlayer = player1Symbol;
    gameRunning = true;

    while (gameRunning)
    {
        board.displayBoard();
        int row, col;
        while (true) {
            std::cout << (currentPlayer == player1Symbol ? player1Name : player2Name) 
                      << " (" << currentPlayer << "), entrez votre coup (ligne colonne) : ";
            if (!(std::cin >> row >> col)) {
                std::cout << "Entrée invalide. Veuillez entrer des nombres pour la ligne et la colonne.\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                continue;
            }

            if (row < 0 || row >= board.getSize() || col < 0 || col >= board.getSize()) {
                std::cout << "Position hors des limites. Veuillez entrer des valeurs entre 0 et " 
                          << board.getSize() - 1 << ".\n";
                continue;
            }

            if (!board.isCellFree(row, col)) {
                std::cout << "La cellule est déjà occupée. Choisissez une autre position.\n";
                continue;
            }

            if (board.updateCell(row, col, currentPlayer)) {
                break;
            }
        }

        if (checkWin())
        {
            board.displayBoard();
            std::cout << (currentPlayer == player1Symbol ? player1Name : player2Name) 
                      << " (" << currentPlayer << ") a gagné !\n";
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
}

void Play::switchPlayer() {
    currentPlayer = (currentPlayer == player1Symbol) ? player2Symbol : player1Symbol;
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
