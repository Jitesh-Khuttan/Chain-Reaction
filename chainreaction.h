#include<iostream>
#include<string>
#include<string.h>
using namespace std;


const int LENGTH = 9;
const int WIDTH = 6;
const char BLACK = 'b';
const char RED = 'r';
const char GREEN = 'g';


class ChainReaction
{
	private:
        typedef struct
        {
            char value;
            char mass;
            char color;
        }Board;
        char player1color,player2color;
        Board gameBoard[9][6];
	public:
		ChainReaction();
		void printBoard();
		void insertValue(int row,int column,char color);
		bool checkCellDimension(int row,int column);
		void setPlayerColor(char,int);
		int checkWinner();
		bool checkValidEntry(int row,int column,char color);
};


