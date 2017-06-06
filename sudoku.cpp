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

std::pair<int, int> Sudoku::setFieldToFill()
{
  std::pair<int, int> field; // row, column

  int row;
  int column;

  do {

    char columnChar;

    std::cout << "podaj pole do wypelnienia: [np.:A 1]";
    std::cin >> columnChar >> row;
    std::cin.clear();
    std::cin.sync();

    columnChar = std::toupper(columnChar);

    std::cout << columnChar << "kolumna   \n";
    std::cout << row << "rzad   \n";
    column = columnChar - 64;

    std::cout << column << "kolumna po konwersji   \n";
    std::cout << row << "rzad   \n";

  } while(!(row >= 1 && row <= 9 && column >=1 && column <= 9));

  field.first = row - 1;
  field.second = column - 1;

  std::cout << field.first << "   ";
  std::cout << field.second;
  return field;
}

int Sudoku::setValue()
{
  int value;
  std::cout << "podaj wartosc od 1 do 9: ";
  std::cin >> value;
  return value;
}

void Sudoku::fillingField(std::pair<int, int> field, int value)
{
  modifiableSudokuBoard[field.first][field.second] = value;
}
