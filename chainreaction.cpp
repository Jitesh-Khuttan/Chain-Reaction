#include "chainreaction.h"

ChainReaction :: ChainReaction()
{
	int i,j;
	for(i=0;i<LENGTH;i++)
	{
		for(j=0;j<WIDTH;j++)
		{
			gameBoard[i][j].value = 32;
			gameBoard[i][j].color = BLACK;
		}
	}

	//Initializing The Weights Of The gameBoard(Assigning Mass To The Corners)
	gameBoard[0][0].mass = 50;
	gameBoard[8][0].mass = 50;
	gameBoard[8][5].mass = 50;
	gameBoard[0][5].mass = 50;

	//Initializing The Weights Of The gameBoard(Assigning Mass To The Normal Cells)

	for(i=1;i<LENGTH-1;i++)
	{
        for(j=1;j<WIDTH-1;j++)
        {
            gameBoard[i][j].mass = 52;
        }
	}

	//Initializing The Weights Of The gameBoard(Assigning Mass To The Edge Cells)

    for(i=1;i<WIDTH-1;i++)
    {
        gameBoard[0][i].mass = 51;
        gameBoard[8][i].mass = 51;
    }

    for(i=1;i<LENGTH-1;i++)
    {
        gameBoard[i][0].mass = 51;
        gameBoard[i][5].mass = 51;
    }
}

void ChainReaction :: printBoard()
{
    int i,j;
    cout<<"\n\t  ";
    for(i=0;i<WIDTH;i++)
    {
        cout<<"  "<<i+1<<"  ";
    }
    for(i=0;i<LENGTH;i++)
	{
        cout<<"\n\t  -------------------------------";
        cout<<"\n\t"<<i+1<<" |";
		for(j=0;j<WIDTH;j++)
		{
			cout<<" "<<gameBoard[i][j].value;
			if(gameBoard[i][j].color != BLACK)
                cout<<gameBoard[i][j].color<<" |";
            else
		        cout<<"  |";
        }
	}
	cout<<"\n\t  -------------------------------";
}


void ChainReaction :: insertValue(int row,int column,char color)
{
    //Check If The Cell Is Stable Or Not
    if(gameBoard[row][column].value < (gameBoard[row][column].mass - 1))
    {
        gameBoard[row][column].color = color;
        if(gameBoard[row][column].value == 32)
        {
            gameBoard[row][column].value = 49;
        }
        else
        {
            gameBoard[row][column].value += 1;
        }
    }
    //If The Cell Is Equal To Its Critical Mass - 1 (Then The Cell Will Explode And Recursively Call Its Orthogonal Neighbours)
    else if (gameBoard[row][column].value == (gameBoard[row][column].mass - 1))
    {
        gameBoard[row][column].value = 32;
        gameBoard[row][column].color = BLACK;
        if(gameBoard[row][column].mass == 50) //If Critical Mass is 2
        {
            if(row == 0 && column == 0) //If The Cell Is A Top Left Cell [0][0]
            {
                insertValue(row,column+1,color); //[0][1]
                insertValue(row+1,column,color); //[1][0]
            }
            else if(row == 8 && column == 0) //If The Cell Is A Bottom Left Cell [8][0]
            {
                insertValue(row,column+1,color); //[8][1]
                insertValue(row-1,column,color); //[7][0]
            }
            else if(row == 0 && column == 5) //If The Cell Is A Top Right Cell [0][5]
            {
                insertValue(row,column-1,color); //[0][4]
                insertValue(row+1,column,color); //[1][5]
            }
            else if(row == 8 && column == 5) //If The Cell Is A Bottom Right Cell [8][5]
            {
                insertValue(row,column-1,color); //[8][4]
                insertValue(row-1,column,color); //[7][5]
            }
        }
        else if(gameBoard[row][column].mass == 51) //If Critical Mass is 3
        {
            if(row == 0)
            {
                insertValue(row,column-1,color);
                insertValue(row,column+1,color);
                insertValue(row+1,column,color);
            }
            else if(row == 8)
            {
                insertValue(row,column-1,color);
                insertValue(row,column+1,color);
                insertValue(row-1,column,color);
            }
            else if(column == 0)
            {
                insertValue(row-1,column,color);
                insertValue(row+1,column,color);
                insertValue(row,column+1,color);
            }
            else if(column == 5)
            {
                insertValue(row-1,column,color);
                insertValue(row+1,column,color);
                insertValue(row,column-1,color);
            }
        }
        else if(gameBoard[row][column].mass == 52) //If Critical Mass is 4
        {
            insertValue(row-1,column,color);
            insertValue(row,column-1,color);
            insertValue(row+1,column,color);
            insertValue(row,column+1,color);
        }
    }
}

bool ChainReaction :: checkCellDimension(int row,int column)
{
    if(row < 0 || row > 8 || column < 0 || column > 5)
        return false;
    return true;
}


void ChainReaction :: setPlayerColor(char color,int playerNumber)
{
    if(playerNumber == 1)
        player1color = color;
    else if(playerNumber == 2)
        player2color = color;
}

int ChainReaction :: checkWinner()
{
    int redColor=0,greenColor=0;
    int i,j;
    for(i=0;i<LENGTH;i++)
    {
        for(j=0;j<WIDTH;j++)
        {
            if(gameBoard[i][j].color == RED)
                redColor++;
            else if(gameBoard[i][j].color == GREEN)
                greenColor++;
        }
    }
    if(redColor == 0)
    {
        if(player1color == RED)
            return 2;
        else if(player2color == RED)
            return 1;
    }
    else if(greenColor == 0)
    {
        if(player1color == GREEN)
            return 2;
        else if(player2color == GREEN)
            return 1;
    }
    return -1;
}


bool ChainReaction :: checkValidEntry(int row,int column,char color)
{
    if(color == RED)
    {
        if(gameBoard[row][column].color == GREEN)
            return false;
        return true;
    }
    else if(color == GREEN)
    {
        if(gameBoard[row][column].color == RED)
            return false;
        return true;
    }
}

