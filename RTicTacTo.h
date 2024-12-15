#ifndef LIFE_OF_GAME_RTICTACTO_H
#define LIFE_OF_GAME_RTICTACTO_H

#include "BoardGame_Classes.h"

template <typename T>
class RTicTacTo : public Board<T> {
public:
    RTicTacTo();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class RTicTacTo_Player : public Player<T> {
public:
    RTicTacTo_Player(std::string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class RTicTacTo_Random_Player : public RandomPlayer<T> {
public:
    RTicTacTo_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for RTicTacTo
template <typename T>
RTicTacTo<T>::RTicTacTo() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool RTicTacTo<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void RTicTacTo<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
int check_winner = -1, Xposi,Oposi;
bool last_mov = false;
template <typename T>
bool RTicTacTo<T>::is_win() {
    if (this->n_moves == check_winner) {
        return true;
    }
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            check_winner = this->n_moves + 1;
            last_mov = true;
        } else if (this->board[i][0] == 0) {
            Xposi = i;
            Oposi = 0;
        } else if (this->board[0][i] == 0) {
            Xposi = 0;
            Oposi = i;
        }
    }
    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        check_winner = this->n_moves + 1;
        last_mov = true;
    } else if (this->board[0][0] == 0) {
        Xposi = 0;
        Oposi = 0;
    } else if (this->board[0][2] == 0) {
        Xposi = 0;
        Oposi = 2;
    }
    return false;
}
// Return true if 10 moves are done and no winner
template <typename T>
bool RTicTacTo<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool RTicTacTo<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for RTicTacTo_Player
template <typename T>
RTicTacTo_Player<T>::RTicTacTo_Player(std::string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void RTicTacTo_Player<T>::getmove(int& x, int& y) {
    if (last_mov) {
        x = Xposi;
        y = Oposi;
        return;
    }
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for RTicTacTo_Random_Player
template <typename T>
RTicTacTo_Random_Player<T>::RTicTacTo_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void RTicTacTo_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

#endif // LIFE_OF_GAME_RTICTACTO_H