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
    std::pair<int, int> setFieldToFill();
    int setValue();
    void fillingField(std::pair<int, int> field, int value);
    int checkUp(); //sprawdzenei calej tablicy jesli wszystkie pola sa wypelnione
};

#endif // SUDOKU_H
