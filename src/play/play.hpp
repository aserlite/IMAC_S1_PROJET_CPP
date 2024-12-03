#ifndef PLAY_HPP
#define PLAY_HPP

#include "../genBoard/genBoard.hpp"
#include "../AI/AI.hpp"

class Play {
public:
    Play(int boardSize);

    void startSoloGame();

    void startDuoGame();

    ~Play();

private:
    GenBoard board; 
    AI ai; 
    
    char currentPlayer; 

    void switchPlayer();

    bool checkWin() const;

    bool checkDraw() const;
};

#endif // PLAY_HPP
