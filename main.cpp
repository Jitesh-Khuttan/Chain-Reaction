#include "chainreaction.cpp"
#include<random>
#include<ctime>

int main()
{
    int row,column,winner=-1,result;

    default_random_engine randomGenerator(time(0));
    uniform_int_distribution<int> coin(1,4);
    int color,loop=0;
    char player1color,player2color;
    bool check;
    ChainReaction game;

    cout<<"\n\t**************************TOSS**************************";
    result = coin(randomGenerator);
    if(result == 1 || result == 3)
    {
        while(1)
        {
            cout<<"\n\tPlayer 1 Won The Toss\n\tChoose Your Color\n\t1.RED\n\t2.GREEN\n\t";
            cin>>color;
            if(color == 1)
            {
                player1color = RED;
                player2color = GREEN;
                game.setPlayerColor(RED,1);
                game.setPlayerColor(GREEN,2);
                break;
            }
            else if(color == 2)
            {
                player1color = GREEN;
                player2color = RED;
                game.setPlayerColor(GREEN,1);
                game.setPlayerColor(RED,2);
                break;
            }
            else
            {
                cout<<"\n\tPlease Choose Valid Option";
            }
        }
    }
    else if(result == 2 || result==4)
    {
        while(1)
        {
            cout<<"\n\tPlayer 2 Won The Toss\n\tChoose Your Color\n\t1.RED\n\t2.GREEN\n\t";
            cin>>color;
            if(color == 1)
            {
                player2color = RED;
                player1color = GREEN;
                game.setPlayerColor(RED,2);
                game.setPlayerColor(GREEN,1);
                game.printBoard();
                goto PLAYER_2_TURN;
            }
            else if(color == 2)
            {
                player2color = GREEN;
                player1color = RED;
                game.setPlayerColor(GREEN,2);
                game.setPlayerColor(RED,1);
                game.printBoard();
                goto PLAYER_2_TURN;
            }
            else
            {
                cout<<"\n\tPlease Choose Valid Option";
            }
        }
    }

    game.printBoard();
    while(winner==-1)
    {
        loop++;
        //cout<<"\n\tLoop: "<<loop;
        cout<<"\n\tPlayer 1";
        while(1)
        {
            cout<<"\n\tEnter Row: ";
            cin>>row;
            cout<<"\n\tEnter Column: ";
            cin>>column;
            check = game.checkCellDimension(row-1,column-1);
            if(check == true)
            {
                if(game.checkValidEntry(row-1,column-1,player1color))
                {
                    game.insertValue(row-1,column-1,player1color);
                    break;
                }
                else
                    cout<<"\n\tYou Cannot Enter On Other Players Cell";
            }
            else
                cout<<"\n\tEnter Valid Cell Dimension";
        }
        game.printBoard();
        if(loop>1)
            winner = game.checkWinner();
        if(winner == 1)
        {
            cout<<"\n\tPlayer 1 Won The Game\n";
            break;
        }
        PLAYER_2_TURN:
        cout<<"\n\tPlayer 2";
        while(1)
        {
            cout<<"\n\tEnter Row: ";
            cin>>row;
            cout<<"\n\tEnter Column: ";
            cin>>column;
            check = game.checkCellDimension(row-1,column-1);
            if(check == true)
            {
                if(game.checkValidEntry(row-1,column-1,player2color))
                {
                    game.insertValue(row-1,column-1,player2color);
                    break;
                }
                else
                    cout<<"\n\tYou Cannot Enter On Other Players Cell";
            }
            else
                cout<<"\n\tEnter Valid Cell Dimension";
        }
        game.printBoard();

        if(loop>1)
            winner = game.checkWinner();
        if(winner == 2)
            cout<<"\n\tPlayer 2 Won The Game\n";
    }
    return 0;
}
