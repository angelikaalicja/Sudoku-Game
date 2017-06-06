#include <iostream>
#include "sudoku.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    Sudoku s("board.txt");
    s.loadData();
    s.drawBoard();
    return 0;
}
