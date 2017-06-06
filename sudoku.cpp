#define __USE_MINGW_ANSI_STDIO 0
#include "sudoku.h"


#include <iostream>
#include <fstream>

Sudoku::Sudoku(const std::string& filename)
{
  dataFile = filename;
}

void Sudoku::loadData()
{
       std::ifstream board(dataFile.c_str());

       if(board.good()==false)
       {
          std::cout<<"Data file is missing!";
          exit(1); // do zmiany
       }

       for (int column = 0; column < 9; column++)
       {
          for (int row = 0; row < 9; row++)
          {
             board >> sudokuBoard[row][column];
          }

       }
       board.close();

       for (int column = 0; column < 9; column++)
       {
          for (int row = 0; row < 9; row++)
          {
             modifiableSudokuBoard[row][column] = sudokuBoard[row][column];
          }
       }
}

void Sudoku::drawBoard()
{
  std::string sudokuBoardString[9][9];

  for (int column = 0; column < 9; column++)
  {
     for (int row = 0; row < 9; row++)
     {
        sudokuBoardString[row][column] = std::to_string(modifiableSudokuBoard[row][column]);
        if (sudokuBoardString[row][column] == "0")
        {
           sudokuBoardString[row][column] = " ";
        }
     }

  }

    std::cout << "   A B C D E F G H I" << std::endl << std::endl;
    for (int row = 0; row < 9; row++)
    {
          int printedRow = row+1;
          std::cout << printedRow << "  "
           << sudokuBoardString[0][row]
           << " " << sudokuBoardString[1][row]
           << " " << sudokuBoardString[2][row]
           << "|"
           << sudokuBoardString[3][row]
           << " " << sudokuBoardString[4][row]
           << " " << sudokuBoardString[5][row]
           << "|"
           << sudokuBoardString[6][row]
           << " " << sudokuBoardString[7][row]
           << " " << sudokuBoardString[8][row]
           << std::endl;

           if (row == 2 || row == 5 )
           {
             std::cout << "   -----+-----+-----" << std::endl;
           }
    }
}
