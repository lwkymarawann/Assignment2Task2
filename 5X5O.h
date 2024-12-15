#ifndef LIFE_OF_GAME_5X5O_H
#define LIFE_OF_GAME_5X5O_H

#include "BoardGame_Classes.h"

template <typename T>
class X_O_Board_5x5 : public Board<T> {
public:
    X_O_Board_5x5();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class X_O_Player_5x5 : public Player<T> {
public:
    X_O_Player_5x5(std::string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class X_O_Random_Player_5x5 : public RandomPlayer<T> {
public:
    X_O_Random_Player_5x5(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board_5x5
template <typename T>
X_O_Board_5x5<T>::X_O_Board_5x5() {
    this->rows = this->columns = 5;
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
bool X_O_Board_5x5<T>::update_board(int x, int y, T mark) {
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
void X_O_Board_5x5<T>::display_board() {
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
bool last_move = false;
int Xpos, Opos;
// Returns true if there is any winner
template <typename T>
bool X_O_Board_5x5<T>::is_win() {
    static int p1, p2;
    if (this->n_moves == 25 && p1 > p2) { // Player 1 wins
        return true;
    }
    if (this->n_moves == 23) {
        p1 = 0;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] != 0) {
                    // Check for vertical matches
                    if (i <= this->rows - 3 && this->board[i][j] == 'X' && this->board[i + 1][j] == 'X' && this->board[i + 2][j] == 'X') {
                        p1++;
                    }
                    // Check for horizontal matches
                    if (j <= this->columns - 3 && this->board[i][j] == 'X' && this->board[i][j + 1] == 'X' && this->board[i][j + 2] == 'X') {
                        p1++;
                    }
                    // Check for left-to-right diagonal matches
                    if (i <= this->rows - 3 && j <= this->columns - 3 && this->board[i][j] == 'X' && this->board[i + 1][j + 1] == 'X' && this->board[i + 2][j + 2] == 'X') {
                        p1++;
                    }
                    // Check for right-to-left diagonal matches
                    if (i <= this->rows - 3 && j >= 2 && this->board[i][j] == 'X' && this->board[i + 1][j - 1] == 'X' && this->board[i + 2][j - 2] == 'X') {
                        p1++;
                    }
                }
            }
        }
    } else if (this->n_moves == 24) {
        p2 = 0;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] != 0) {
                    // Check for vertical matches
                    if (i <= this->rows - 3 && this->board[i][j] == 'O' && this->board[i + 1][j] == 'O' && this->board[i + 2][j] == 'O') {
                        p2++;
                    }
                    // Check for horizontal matches
                    if (j <= this->columns - 3 && this->board[i][j] == 'O' && this->board[i][j + 1] == 'O' && this->board[i][j + 2] == 'O') {
                        p2++;
                    }
                    // Check for left-to-right diagonal matches
                    if (i <= this->rows - 3 && j <= this->columns - 3 && this->board[i][j] == 'O' && this->board[i + 1][j + 1] == 'O' && this->board[i + 2][j + 2] == 'O') {
                        p2++;
                    }
                    // Check for right-to-left diagonal matches
                    if (i <= this->rows - 3 && j >= 2 && this->board[i][j] == 'O' && this->board[i + 1][j - 1] == 'O' && this->board[i + 2][j - 2] == 'O') {
                        p2++;
                    }
                } else if (this->board[i][j] == 0) {
                    Xpos = i;
                    Opos = j;
                }
            }
        }
        last_move = true;
    }
    if (this->n_moves == 24 && p2 > p1) {
        return true; // Player 2 wins
    }
    return false;
}

// Return false if 25 moves are done and no winner
template <typename T>
bool X_O_Board_5x5<T>::is_draw() {
    return (this->n_moves == 25 && !is_win());
}

template <typename T>
bool X_O_Board_5x5<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for X_O_Player_5x5
template <typename T>
X_O_Player_5x5<T>::X_O_Player_5x5(std::string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player_5x5<T>::getmove(int& x, int& y) {
    if (last_move) {
        x = Xpos;
        y = Opos;
        return;
    }
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player_5x5
template <typename T>
X_O_Random_Player_5x5<T>::X_O_Random_Player_5x5(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_Random_Player_5x5<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 4
    y = rand() % this->dimension;
}

#endif // LIFE_OF_GAME_5X5O_H