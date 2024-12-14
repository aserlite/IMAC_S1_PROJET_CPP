#include "AI.hpp"
#include <limits>
#include <vector>

AI::AI() {}

std::pair<int, int> AI::calculateMove(std::vector<std::vector<char>> boardState, char aiPlayer) {
    char humanPlayer = (aiPlayer == 'X') ? 'O' : 'X';
    int bestVal = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    for (size_t i = 0; i < boardState.size(); ++i) {
        for (size_t j = 0; j < boardState[i].size(); ++j) {
            if (boardState[i][j] == ' ') {
                boardState[i][j] = aiPlayer;

                int moveVal = minimax(boardState, false, aiPlayer, humanPlayer);

                boardState[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}


int AI::minimax(std::vector<std::vector<char>>& boardState, bool isMaximizing, char aiPlayer, char humanPlayer, int depth = 0) {
    int score = evaluate(boardState, aiPlayer, humanPlayer);

    if (score == 10 || score == -10 || depth >= 6) {
        return score;
    }

    if (!isMovesLeft(boardState)) {
        return 0;
    }

    if (isMaximizing) {
        int best = std::numeric_limits<int>::min();

        for (size_t i = 0; i < boardState.size(); ++i) {
            for (size_t j = 0; j < boardState[i].size(); ++j) {
                if (boardState[i][j] == ' ') {
                    boardState[i][j] = aiPlayer;
                    best = std::max(best, minimax(boardState, false, aiPlayer, humanPlayer, depth + 1));
                    boardState[i][j] = ' ';
                }
            }
        }
        return best;
    }

    else {
        int best = std::numeric_limits<int>::max();

        for (size_t i = 0; i < boardState.size(); ++i) {
            for (size_t j = 0; j < boardState[i].size(); ++j) {
                if (boardState[i][j] == ' ') {
                    boardState[i][j] = humanPlayer;
                    best = std::min(best, minimax(boardState, true, aiPlayer, humanPlayer, depth + 1));
                    boardState[i][j] = ' ';
                }
            }
        }
        return best;
    }
}


bool AI::isMovesLeft(const std::vector<std::vector<char>>& boardState) const {
    for (const auto& row : boardState) {
        for (const auto& cell : row) {
            if (cell == ' ') {
                return true;
            }
        }
    }
    return false;
}

int AI::evaluate(const std::vector<std::vector<char>>& boardState, char aiPlayer, char humanPlayer) const {
    for (size_t row = 0; row < boardState.size(); ++row) {
        if (boardState[row][0] == boardState[row][1] && boardState[row][1] == boardState[row][2]) {
            if (boardState[row][0] == aiPlayer) return +10;
            if (boardState[row][0] == humanPlayer) return -10;
        }
    }

    for (size_t col = 0; col < boardState[0].size(); ++col) {
        if (boardState[0][col] == boardState[1][col] && boardState[1][col] == boardState[2][col]) {
            if (boardState[0][col] == aiPlayer) return +10;
            if (boardState[0][col] == humanPlayer) return -10;
        }
    }

    if (boardState[0][0] == boardState[1][1] && boardState[1][1] == boardState[2][2]) {
        if (boardState[0][0] == aiPlayer) return +10;
        if (boardState[0][0] == humanPlayer) return -10;
    }

    if (boardState[0][2] == boardState[1][1] && boardState[1][1] == boardState[2][0]) {
        if (boardState[0][2] == aiPlayer) return +10;
        if (boardState[0][2] == humanPlayer) return -10;
    }

    return 0;
}

AI::~AI() {}
