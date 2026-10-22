/*
  base.cpp
  Jeremiah Cummings
  10/21/26
  This is intened to be the most incredibly basic in/out of the board possible.
  I'm also just setting the stage for the feel of the code, if that makes any sense.
  Reads in an r x c board from stdin (for now, will read a file later) and prints it.
*/

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

/*
  Prints the board.
  Include brief description above each function/method, please.
*/
void print(vector<vector<char> > board)
{
    size_t i, j;
    for(i = 0; i < board.size(); i++) {
        for(j = 0; j < board[i].size(); j++) {
            printf("%c ", board[i][j]);
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<char> > board;
    size_t i, j, r, c;
    char in;
    
    // read board, size r x c
    cin >> r >> c;
    board.resize(r);

    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            cin >> in;
            board[i].push_back(in);
        }
    }
    
    print(board);
    return 0;
}