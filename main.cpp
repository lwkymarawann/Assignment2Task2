// MADE BY: Marawan Mohamed Abd El-Hamid ID: 20230557, GAME 6


#include <iostream>
#include <ctime>
#include <string>
using namespace std;

void drawBoard(char *board){
    cout << "     |     |     " << endl;
    cout << "  "<< board[0] <<"  |  "<< board[1] <<"  |  "<< board[2] <<"  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  "<< board[3] <<"  |  "<< board[4] <<"  |  "<< board[5] <<"  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  "<< board[6] <<"  |  "<< board[7] <<"  |  "<< board[8] <<"  " << endl;
}
void playerMove(char *board, char Player){
    int number;
    do
    {
        cout << "Enter a spot to play your move (1-9): ";
        cin >> number;
        number--;
        if(board[number] == ' '){
            board[number] = Player;
            break;
        }
    }
    while(!number > 0 || !number < 8);

}
void aiMove(char *board, char AI){
    int number;
    srand(time(0));

    while(true){

        number = rand() % 9;

        if(board[number] == ' '){
            board[number] = AI;
            break;
        }
    }

}
bool checkWinner(char *board, char Player, char AI){
    // row 1
    if(board[0] != ' ' && board[0] == board[1] && board[1] == board[2]){
        board[0] == AI ? cout << "Player WINS (ON ROW 1)" << endl : cout << "AI WINS (ON ROW 1)" << endl;
        return true;
    }
    // row 2
    else if(board[3] != ' ' && board[3] == board[4] && board[4] == board[5]){
        board[3] == AI ? cout << "Player WINS (ON ROW 2)" << endl : cout << "AI WINS (ON ROW 2)" << endl;
        return true;
    }
    // row 3
    else if(board[6] != ' ' && board[6] == board[7] && board[7] == board[8]){
        board[6] == AI ? cout << "Player WINS (ON ROW 3)" << endl : cout << "AI WINS (ON ROW 3)" << endl;
        return true;
    }
    // column 1
    else if(board[0] != ' ' && board[0] == board[3] && board[3] == board[6]){
        board[0] == AI ? cout << "Player WINS (ON COLUMN 1)" << endl : cout << "AI WINS (ON COLUMN 1)" << endl;
        return true;
    }
    // column 2
    else if(board[1] != ' ' && board[1] == board[4] && board[4] == board[7]){
        board[1] == AI ? cout << "Player WINS (ON COLUMN 2)" << endl : cout << "AI WINS (ON COLUMN 2)" << endl;
        return true;
    }
    // column 3
    else if(board[2] != ' ' && board[2] == board[5] && board[5] == board[8]){
        board[2] == AI ? cout << "Player WINS (ON COLUMN 3)" << endl : cout << "AI WINS (ON COLUMN 3)" << endl;
        return true;
    }
    // diagonal 1
    else if(board[0] != ' ' && board[0] == board[4] && board[4] == board[8]){
        board[0] == AI ? cout << "Player WINS (ON DIAGONAL 1)" << endl : cout << "AI WINS (ON DIAGONAL 1)" << endl;
        return true;
    }
    // diagonal 2
    else if(board[2] != ' ' && board[2] == board[4] && board[4] == board[6]){
        board[2] == AI ? cout << "Player WINS (ON DIAGONAL 2)" << endl : cout << "AI WINS (ON DIAGONAL 2)" << endl;
        return true;
    }
    else{
        return false;
    }
    
    return false;
}
bool checkDraw(char *board){
    
    for(int i = 0; i < 9; i++){
        if(board[i] == ' '){
            return false;
            
        }
    }
    cout << "IT'S A DRAW" << endl;
        return true;
}

int main()
{
    // Decleration of variables
    char board[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    char Player = 'X';
    char AI = 'O';
    bool running = true;


    //GAME NAME

    cout << "#########################" << endl;
    cout << "    Misere Tic Tac Toe   " << endl;
    cout << "#########################" << endl;
    cout << "also known as Inverse Tic Tac Toe" << endl;
    cout << "a game where to win you must lose"  << endl;
    cout << "(to win the you must force your opponent to get three in a row)" << endl;


    // Running functions

    drawBoard(board);

    while(running){
        playerMove(board, Player);
        drawBoard(board);
        cout <<  "**********************************"<< endl;
        if(checkWinner(board, Player, AI)){
            running = false;
            break;
        }
        else if(checkDraw(board)){

            running = false;
            break;
        }


        aiMove(board, AI);
        drawBoard(board);
        cout <<  "**********************************"<< endl;
        if(checkWinner(board, Player, AI)){
            running = false;
            break;
        }
        else if(checkDraw(board)){

            running = false;
            break;
        }

    }
    cout << "********************" << endl;
    cout << "THANKS FOR PLAYING!!" << endl;
    cout << "********************" << endl;



}