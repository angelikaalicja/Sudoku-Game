#include <iostream>
#include <chrono>
#include <ctime>

#include "sudoku.h"

using namespace std::chrono;

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

  std::chrono::time_point<std::chrono::system_clock> start, end;

  start = std::chrono::system_clock::now();

  if (s.checkBoard() == true)
  {
    std::cout << "Good job!\n";
  }
  else
  {
    std::cout << "Sudoku is not solved!\n";
  }

  end = std::chrono::system_clock::now();
  std::chrono::duration<long double> elapsed_seconds = end-start;

  std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";



  return 0;
}
