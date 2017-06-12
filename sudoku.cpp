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

bool Sudoku::checkBoard()
{
  std::set<int> correctGroup { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  //checking rows
  for (int row = 0; row < 9; row++)
  {
    std::set<int> groupToReview;
    for (int column = 0; column < 9; column++)
    {
      groupToReview.insert(modifiableSudokuBoard[row][column]);
    }
    if (groupToReview != correctGroup)
    {
      return false;
    }
  }

  //checking columns
  for (int column = 0; column < 9; column++)
  {
    std::set<int> groupToReview;
    for (int row = 0; row < 9; row++)
    {
      groupToReview.insert(modifiableSudokuBoard[row][column]);
    }
    if (groupToReview != correctGroup)
    {
      return false;
    }
  }

  //checking 3x3 squares
  for (int boxRow = 0; boxRow < 3; boxRow++)
  {
    for (int boxColumn = 0; boxColumn < 3; boxColumn++)
    {
      std::set<int> groupToReview;

      for (int i = boxRow * 3; i < boxRow * 3 + 3; i++)
      {
        for (int j = boxColumn * 3; j < boxColumn * 3 + 3; j++)
        {
          groupToReview.insert(modifiableSudokuBoard[i][j]);
        }
      }

      if (groupToReview != correctGroup)
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

// C-style check board

bool Sudoku::checkValueC(int row, int column)
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

bool Sudoku::checkBoardC()
{
  for (int row = 0; row < 9; row++)
  {
    for (int column = 0; column < 9; column++)
    {
      if (checkValueC(row, column) == false)
      {
        return false;
      }
    }
  }

  return true;
}

bool Sudoku::isInRow(int row, int value)
{
  for (int column = 0; column < 9; column++)
  {
    if (modifiableSudokuBoard[row][column] == value)
    {
      return true;
    }
  }
  return false;
}

bool Sudoku::isInColumn(int column, int value)
{
  for (int row = 0; row < 9;  row++)
  {
    if (modifiableSudokuBoard[row][column] == value)
    {
      return true;
    }
  }
  return false;
}

bool Sudoku::isInBox(int row, int column, int value)
{
  int squareRow = row / 3;
  int squareColumn = column / 3;

  for (int i = squareRow * 3; i < squareRow * 3 + 3; i++)
  {
    for (int j = squareColumn * 3; j < squareColumn * 3 + 3; j++)
    {
      if (modifiableSudokuBoard[i][j] == value)
      {
        return true;
      }
    }
  }
  return false;
}

bool Sudoku::isPossible(int row, int column, int value)
{
  if (isInRow(row, value) || isInColumn(column, value) || isInBox(row, column, value))
  {
    return false;
  }
  return true;
}

bool Sudoku::findEmptyField(int &row, int &column)
{
  for (row = 0; row < 9; row++)
  {
    for (column = 0; column <9; column++)
    {
      if (modifiableSudokuBoard[row][column] == 0)
      {
        return true;
      }
    }
  }
  return false;
}

bool Sudoku::solve()
{
  int row, column;

  if (!findEmptyField(row, column))
  {
    return true;
  }

  for (int value = 1; value <= 9; value++)
    {
      if (isPossible(row, column, value))
      {
        modifiableSudokuBoard[row][column] = value;
        if (solve())
        {
          return true;
        }
        else
        {
          modifiableSudokuBoard[row][column] = 0;
        }
      }
    }
    return false;
}
