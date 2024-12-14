#ifndef GENBOARD_HPP
#define GENBOARD_HPP

#include <vector>

class GenBoard {
public:
    GenBoard(int size);

    void displayBoard() const;

    bool updateCell(int row, int col, char player);

    bool isCellFree(int row, int col) const;

    char getCell(int row, int col) const;

    std::vector<std::vector<char>> getState() const ;

    int getSize() const ;

    ~GenBoard();

private:
    int size;
    std::vector<std::vector<char>> grid; 
};

#endif // GENBOARD_HPP
