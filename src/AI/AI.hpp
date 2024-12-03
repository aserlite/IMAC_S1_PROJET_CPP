#ifndef AI_HPP
#define AI_HPP

#include <vector>
#include <utility>

class AI {
public:
    AI();

    std::pair<int, int> calculateMove(std::vector<std::vector<char>> boardState, char aiPlayer);

    ~AI();

private:
    int minimax(std::vector<std::vector<char>>& boardState, bool isMaximizing, char aiPlayer, char humanPlayer);
    bool isMovesLeft(const std::vector<std::vector<char>>& boardState) const;
    int evaluate(const std::vector<std::vector<char>>& boardState, char aiPlayer, char humanPlayer) const;
};

#endif // AI_HPP
