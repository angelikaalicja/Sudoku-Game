#include <iostream>
#include "sudoku.h"

using namespace std;

int main()
{
  Sudoku s("board4.txt");
  s.loadData();
  s.drawBoard();

  while (s.checkIfFilledOut() == false)
  {
    std::pair<int, int> field;
    int value;
    field = s.setFieldToFill();
    value = s.setValue();
    s.fillingField(field, value);
    s.drawBoard();
  }

  if (s.checkBoard() == true)
  {
    std::cout << "Good job!\n";
  }
  else
  {
    std::cout << "Sudoku is not solved!\n";
  }

  return 0;
}
