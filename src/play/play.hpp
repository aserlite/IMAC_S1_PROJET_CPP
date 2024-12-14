#ifndef PLAY_HPP
#define PLAY_HPP

#include "../genBoard/genBoard.hpp"
#include "../AI/AI.hpp"
#include <string>

class Play {
public:
    Play(int boardSize);

    void startSoloGame();
    void startDuoGame();

    ~Play();

private:
    GenBoard board; 
    AI ai; 
    
    std::string player1Name;
    std::string player2Name;
    char player1Symbol;
    char player2Symbol;
    char currentPlayer; 
    bool gameRunning;
    char firstPlayer;

    void switchPlayer();
    bool checkWin() const;
    bool checkDraw() const;
};

#endif // PLAY_HPP
