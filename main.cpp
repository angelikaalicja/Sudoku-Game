#include <iostream>
#include "sudoku.h"

using namespace std;

int main()
{
    Sudoku s("board.txt");
    s.loadData();
    s.drawBoard();

    for (int i =0; i <10; i++)
    {
      std::pair<int, int> field;
      int value;
      field = s.setFieldToFill();
      value = s.setValue();
      s.fillingField(field, value);
      s.drawBoard();
    }

    return 0;
}
