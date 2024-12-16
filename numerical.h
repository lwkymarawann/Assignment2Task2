#ifndef ASSIGNMENT_DEMO_NUMERICAL_H
#define ASSIGNMENT_DEMO_NUMERICAL_H

#include "BoardGame_Classes.h"
#include <string>
#include <vector>

template <typename T>
class numircal_board : public Board<T>{
public:
    // initialize the board
    numircal_board() ;
    // get sure if the move is valid and then update it
    bool update_board(int x, int y, T symbol) ;
    // draw the board
    void display_board() ;
    // check for the wining and draw positions
    bool is_win() ;
    bool is_draw() ;
    // check if the game has been finished
    bool game_is_over() ;
};

template <typename T>
class numerical_player : public Player<T>{
protected:
    T* symbol ;
public:
    // player constructor
    numerical_player(string name , T* symbol ) ;
    // getters for the moves
    void getmove(int &x , int &y ) ;
    T getsymbol() override ;
    bool checkSumbol(int choice ) ;
};

template <typename T>
class numirical_random_player : public RandomPlayer<T>{
public:
    // constructor for the random player
    numirical_random_player(T symbol ) ;
    // generate a possible random move
    void getmove(int &x , int &y) ;
    int findrow(int y, Board<T>*board) ;
};


// ----------------------implementation-----------------------------

/// Board --------------------------------------------------------------------------
template <typename T>
numircal_board<T>::numircal_board(){
    // inserting the board dimensions
    this->rows = 3 ;
    this->columns = 3 ;

    /// initialize the 2D board with a 0 initialization value
    this->board = new char*[this->rows] ;
    for(int i = 0 ; i < this->rows ; i++){
        this->board[i] = new char[this->columns] ;
        for(int j = 0 ; j < this->columns ; j++){
            this->board[i][j] = 0 ;
        }
    }
}

template <typename T>
void numircal_board<T>:: display_board(){
    cout << '\n' ;
    for(int i = 0 ; i < this->rows ; i++){
        for(int j = 0 ; j < this->columns ; j++){
            cout << "|(" << j << ',' << i << ") " << this->board[i][j] << " " ;
        }
        cout << "|\n" ;
    }
    cout << " ___________________________ \n"  ;
}


// check if the move i legal first then modify the board
template <typename T>
bool numircal_board<T> :: update_board(int x, int y, T symbol) {
    // check if the x and y are in the possible range
    if(x >= 0 && x < this->rows && y >= 0 && y < this->columns  ){
        // a way to be able to get remove moves(used for the MinMax algorithm)
        if(symbol == 0){
            this->board[x][y] = 0 ;
            this->n_moves-- ;
            return true ;
        }
        // insert the move if it's a free place
        if(this->board[x][y] == 0 ){
            this->board[x][y] = symbol ;
            this->n_moves++ ;
            return true ;
        }
    }
    return false ;
}

// return true if there's a win
template <typename T>
bool numircal_board<T> :: is_win() {
    for(int i = 0 ; i < this->rows ; i++){
        for(int j = 0 ; j < this->columns ; j++){
            if(this->board[i][j] != 0){ // check only the places with the symbols
                // check the columns and rows
                if(i+2 < this->rows && (this->board[i][j] + this->board[i+1][j] + this->board[i+2][j] ) == 15) return true;
                else if(j+2 < this->columns && (this->board[i][j] + this->board[i][j+1] + this->board[i][j+2]) == 15) return true;
                    // check diagonally
                else if((i + 2 < this->rows && j+2 < this->columns)&& (this->board[i][j] + this->board[i+1][j+1] + this->board[i+2][j+2]) == 15)  return true;
                else if((i + 2 < this->rows && j-2 <= 0)&& (this->board[i][j] + this->board[i+1][j-1] + this->board[i+2][j-2] ) == 15) return true ;
            }
        }
    }
    return false ;
}

// check for draws
template <typename T>
bool numircal_board<T> :: is_draw() {
    if(this->n_moves == 9 && !is_win()){
        return true ;
    }
    return false ;
}

// tell if the game has been finished
template <typename T>
bool numircal_board<T> :: game_is_over() {
    return is_draw() || is_win() ;
}

/// player ---------------------------------------------------------------------------------

// constructor for the player
template <typename T>
numerical_player<T>::numerical_player(string name , T* symbol){
    this->name = name ;
    this->symbol = symbol ;
}

// get the move from the terminal
template <typename T>
void numerical_player<T> ::getmove(int &x, int &y) {
    cout << "Enter a valid Y coordination : " ;
    cin >> y ;
    cin >> x ;
}

template <typename T>
T numerical_player<T> ::getsymbol() {
    int choice ;
    cout << "Enter the number you want : \n" ;
    cin >> choice ;
    while(!checkSumbol(choice) && choice != -1 ){
        cout << "Enter the number you want : \n" ;
        cin >> choice ;
    }
    return choice ;
}

template <typename T>
bool numerical_player<T> ::checkSumbol(int choice) {
    for(int i = 0 ; i < 4 ; i++){
        if(this->symbol[i] == choice){
            this->symbol[i] = -1 ;
            return true ;
        }
    }
    return false ;
}

/// random player --------------------------------------------------------------------------
// constructor for the random player
template <typename T>
numirical_random_player<T> ::numirical_random_player(T symbol) : RandomPlayer<T>(symbol){}

template <typename T>
void numirical_random_player<T> :: getmove(int &x, int &y) {
    // generate any random coordination's in the board
    y = rand() % 7 ;
    x = rand() % 6 ;
}
#endif //ASSIGNMENT_DEMO_NUMERICAL_H
