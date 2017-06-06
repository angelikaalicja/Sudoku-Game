#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>


class Sudoku
{
public:
    Sudoku(const std::string &filename);
    void loadData();
    std::string dataFile;
    int sudokuBoard[9][9];
    int modifiableSudokuBoard[9][9];
    void drawBoard(); //rysowanie modifiableSudokuBoard
    void fillingField(int row, int column); //wypelnienei  pojedycnzego pola jesli jest 0 w sudokuboard
    int checkUp(bool isFilled); //sprawdzenei calej tablicy
};

#endif // SUDOKU_H
