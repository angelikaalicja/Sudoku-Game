#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>


class Sudoku
{
public:
  Sudoku(const std::string &filename);

  std::string dataFile;
  int sudokuBoard[9][9];
  int modifiableSudokuBoard[9][9];

  void loadData();
  void drawBoard();
  std::pair<int, int> setFieldToFill();
  int setValue();
  void fillingField(std::pair<int, int> field, int value);
  bool checkIfFilledOut();
  bool checkBoard();

private:
  bool checkValue(int row, int column);
};

#endif // SUDOKU_H
