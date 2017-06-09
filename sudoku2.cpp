#define __USE_MINGW_ANSI_STDIO 0
#include "sudoku.h"

#include <iostream>
#include <fstream>
#include <set>


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
    exit(1);
  }

  for (int row = 0; row < 9; row++)
  {
    for (int column = 0; column < 9; column++)
    {
      board >> sudokuBoard[row][column];
    }
  }

  board.close();

  for (int row = 0; row < 9; row++)
  {
    for (int column = 0; column < 9; column++)
    {
      modifiableSudokuBoard[row][column] = sudokuBoard[row][column];
    }
  }

}

void Sudoku::drawBoard()
{
  std::string sudokuBoardString[9][9];

  for (int row = 0; row < 9; row++)
  {
    for (int column = 0; column < 9; column++)
    {
      sudokuBoardString[row][column] = std::to_string(modifiableSudokuBoard[row][column]);
      if (sudokuBoardString[row][column] == "0")
      {
        sudokuBoardString[row][column] = " ";
      }
    }
  }

  std::cout << "    A B C D E F G H I" << std::endl;
  std::cout << "    -----+-----+-----" << std::endl;
  for (int row = 0; row < 9; row++)
  {
    int printedRow = row+1;
    std::cout << printedRow << "  "
    << "|" << sudokuBoardString[row][0]
    << " " << sudokuBoardString[row][1]
    << " " << sudokuBoardString[row][2]
    << "|"
    << sudokuBoardString[row][3]
    << " " << sudokuBoardString[row][4]
    << " " << sudokuBoardString[row][5]
    << "|"
    << sudokuBoardString[row][6]
    << " " << sudokuBoardString[row][7]
    << " " << sudokuBoardString[row][8]
    << "|"
    << std::endl;

    if (row == 2 || row == 5 )
    {
      std::cout << "    -----+-----+-----" << std::endl;
    }
  }

    std::cout << "    -----+-----+-----" << std::endl << std::endl;
}

std::pair<int, int> Sudoku::setFieldToFill()
{
  std::pair<int, int> field; // row, column

  int row;
  int column;
  bool isPosible;

  do
  {
    isPosible = true;

    char columnChar;

    std::cout << "Enter the field to fill: [e.g.:A1] ";
    std::cin >> columnChar >> row;
    std::cin.clear();
    std::cin.sync();

    columnChar = std::toupper(columnChar);
    column = columnChar - 64;

    if ((sudokuBoard[row - 1][column - 1]) != 0)
    {
     std::cout << "Invalid choice (not changeable)!\n";
     isPosible = false;
    }

  } while ((isPosible == false) || (row < 1) || (row > 9) || (column < 1) || (column > 9));

  field.first = row - 1;
  field.second = column - 1;

  return field;
}

int Sudoku::setValue()
{
  int value;

  do
  {
    std::cout << "Enter a number from 1 to 9: ";
    std::cin >> value;
    std::cin.clear();
    std::cin.sync();

    if (value < 1 || value > 9)
    {
      std::cout << "Invalid choice!\n";
    }
  } while(value < 1 || value > 9);

  return value;
}

void Sudoku::fillingField(std::pair<int, int> field, int value)
{
  modifiableSudokuBoard[field.first][field.second] = value;
}

bool Sudoku::checkValue(int row, int column)
{
  int value = modifiableSudokuBoard[row][column];

  //checking rows
  for (int i = 0; i < 9; i++)
  {
    if (i == column)
    {
      continue;
    }
    if (value == modifiableSudokuBoard[row][i])
    {
      return false;
    }
  }

  //checking columns
  for (int i = 0; i < 9; i++)
  {
    if (i == row)
    {
      continue;
    }
    if (value == modifiableSudokuBoard[i][column])
    {
      return false;
    }
  }

  //checking 3x3 square
  int squareRow = row / 3;
  int squareColumn = column / 3;

  for (int i = squareRow * 3; i < squareRow * 3 + 3; i++)
  {
    for (int j = squareColumn * 3; j < squareColumn * 3 + 3; j++)
    {
      if (i == row && j == column)
      {
        continue;
      }
      if (value == modifiableSudokuBoard[i][j])
      {
        return false;
      }
    }
  }

  return true;
}

bool Sudoku::checkBoard()
{
  for (int row = 0; row < 9; row++)
  {
    for (int column = 0; column < 9; column++)
    {
      if (checkValue(row, column) == false)
      {
        return false;
      }
    }
  }

  return true;
}

bool Sudoku::checkIfFilledOut()
{
  for (int row = 0; row < 9; row++)
  {
    for (int column = 0; column < 9; column++)
    {
      if (modifiableSudokuBoard[row][column] == 0)
      {
        return false;
      }
    }
  }

  return true;
}