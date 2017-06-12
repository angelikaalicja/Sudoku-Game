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

// measuring elapsed time for STL <set>

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

  std::cout << "elapsed time STL <set>: " << elapsed_seconds.count() << "s\n";

  // measuring elapsed time for C-style checkBoardC

    std::chrono::time_point<std::chrono::system_clock> start2, end2;
    start2 = std::chrono::system_clock::now();

    if (s.checkBoardC() == true)
    {
      std::cout << "Good job!\n";
    }
    else
    {
      std::cout << "Sudoku is not solved!\n";
    }

    end2 = std::chrono::system_clock::now();
    std::chrono::duration<long double> elapsed_seconds2 = end2-start2;

    std::cout << "elapsed time C-table: " << elapsed_seconds2.count() << "s\n";


  return 0;
}
