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
  bool checkValueC(int row, int column);
  bool checkBoardC();

  //solving
  bool isInRow(int row, int value);
  bool isInColumn(int column, int value);
  bool isInBox(int row, int column, int value);
  bool isPossible(int row, int column, int value);
  bool findEmptyField(int &row, int &column);
  bool solve();
};

#endif // SUDOKU_H
