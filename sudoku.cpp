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

       std::cout << "oryginalna tablica:\n";
       for (int row = 0; row < 9; row++)
       {
          for (int column = 0; column < 9; column++)
          {
             board >> sudokuBoard[row][column];
             std::cout << sudokuBoard[row][column];
          }
          std::cout << "\n";

       }
       board.close();

       std::cout << "\n";
       std::cout << "modyfikowalna tablica:\n";
       for (int row = 0; row < 9; row++)
       {
          for (int column = 0; column < 9; column++)
          {
             modifiableSudokuBoard[row][column] = sudokuBoard[row][column];
             std::cout << modifiableSudokuBoard[row][column];
          }
          std::cout << "\n";
       }
       std::cout << "\n";
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

    std::cout << "   A B C D E F G H I" << std::endl << std::endl;
    for (int row = 0; row < 9; row++)
    {
      int printedRow = row+1;
      std::cout << printedRow << "  "
       << sudokuBoardString[row][0]
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
  bool isPosible;

  std::cout << "\nmodyfikowalna tablica przed do while:\n";
  for (int row = 0; row < 9; row++)
  {
     for (int column = 0; column < 9; column++)
     {
        std::cout << modifiableSudokuBoard[row][column] << " ";
     }
     std::cout << "\n";
   }

  do {

    isPosible = true;

    // std::cout << "\noryginalna tablica w do while:\n";
    // for (int row = 0; row < 9; row++)
    // {
    //    for (int column = 0; column < 9; column++)
    //    {
    //       std::cout << sudokuBoard[row][column] << " ";
    //    }
    //    std::cout << "\n";
    //  }

    char columnChar;

    std::cout << "podaj pole do wypelnienia: [np.:A1]";
    std::cin >> columnChar >> row;
    std::cin.clear();
    std::cin.sync();

    columnChar = std::toupper(columnChar);

    // std::cout << columnChar << "kolumna   \n";
    // std::cout << row << "rzad   \n";
    column = columnChar - 64;

    // std::cout << column << "kolumna po konwersji   \n";
    // std::cout << row << "rzad   \n";

    if ((sudokuBoard[row - 1][column - 1]) != 0)
    {
     std::cout << "niemodyfikowalne pole\n";
     std::cout << sudokuBoard[row - 1][column - 1] << "w tablicy jest \n";
     isPosible = false;
    }


    std::cout << "row: " << row << " \n";
    std::cout << "column: " << column << " \n";
    std::cout << "isPosible: " << isPosible << " \n";

  } while ((isPosible == false) || (row < 1) || (row > 9) || (column < 1) || (column > 9));

  field.first = row - 1;
  field.second = column - 1;

  // std::cout << "\noryginalna tablica po do while:\n";
  // for (int row = 0; row < 9; row++)
  // {
  //    for (int column = 0; column < 9; column++)
  //    {
  //       std::cout << sudokuBoard[row][column] << " ";
  //    }
  //    std::cout << "\n";
  //  }

  std::cout << field.first << " row\n";
  std::cout << field.second << " column\n";
  std::cout << sudokuBoard[field.first][field.second] << " w oryginalnej tablicy w w polu [" << field.first << "][" <<field.second<<"]\n";

  return field;
}

int Sudoku::setValue()
{
  int value;

 do {

   std::cout << "podaj wartosc od 1 do 9: ";
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
