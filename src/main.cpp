#include "play/play.hpp"
#include <iostream>

int main() {
    Play game(3); 
    std::cout << "1. contre bot \n2. 1 contre 1" << std::endl ;
    int response;
    std::cin >> response;
    while (response != 1 && response != 2) {
        std::cout << "Invalid input. Please enter 1 or 2." << std::endl;
        std::cin >> response;
    }
    
    switch (response)
    {
    case 1:
        game.startSoloGame();
        break;
    case 2:
        game.startDuoGame();
        break;
    default:
        break;
    }
    return 0;
}