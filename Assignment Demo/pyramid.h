#ifndef _PYRAMID_H
#define _PYRAMID_H

#include "BoardGame_Classes.h"
#include "3x3X_O.h"
#include <iostream>
using namespace std;

template <typename T>
class Pyramid : public Board<T> {
public:
    Pyramid() {
        this->rows = 3;
        this->columns = 5; // Set the columns to accommodate the pyramid structure
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns];
        }
        initialize_pyramid();
    }

    ~Pyramid() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    // Update the board for valid pyramid positions only
    bool update_board(int x, int y, T symbol) override {
        if ((x == 0 && y == 0) || // Valid position
            (x == 1 && (y == 0 || y == 1 || y == 2)) || // Valid positions
            (x == 2 && (y >= 0 && y < 5))) { // Valid positions
            if (this->board[x][y] == ' ') { // Check if the cell is empty
                this->board[x][y] = symbol; // Place the symbol on the board
                this->n_moves++; // Increment move count
                return true; // Valid move
            }
        }
        return false; // Invalid move
    }

    void display_board() override {
        cout << "             _____ " << endl;
        cout << "            |     |" << endl;
        cout << "            |  " << this->board[0][0] << "  |" << endl;
        cout << "      ______|_____|______" << endl;
        cout << "      |     |     |     |" << endl;
        cout << "      |  " << this->board[1][0] << "  |  " << this->board[1][1] << "  |  " << this->board[1][2] << "  |" << endl;
        cout << "______|_____|_____|_____|_____" << endl;
        cout << "|     |     |     |     |     |" << endl;
        cout << "|  " << this->board[2][0] << "  |  " << this->board[2][1] << "  |  " << this->board[2][2] << "  |  " << this->board[2][3] << "  |  " << this->board[2][4] << "  |" << endl;
        cout << "|_____|_____|_____|_____|_____|" << endl;
    }

    bool is_win() override {
        // Check horizontal wins
        if(this->board[1][0] != ' ' && this->board[1][0] == this->board[1][1] && this->board[1][1] == this->board[1][2]) {
            return true;
        }
        if(this->board[2][0] != ' ' && this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2]) {
            return true;
        }
        if(this->board[2][1] != ' ' && this->board[2][1] == this->board[2][2] && this->board[2][2] == this->board[2][3]) {
            return true;
        }
        if(this->board[2][2] != ' ' && this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4]) {
            return true;
        }
        // Check vertical wins
        if (this->board[0][0] != ' ' && this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2]) {
            return true;
        }

        // Check diagonal wins
        if (this->board[0][0] != ' ' &&
            this->board[0][0] == this->board[1][2] &&
            this->board[1][1] == this->board[2][4]) {
            return true;
        }
        if (this->board[0][0] != ' ' &&
            this->board[0][0] == this->board[1][0] &&
            this->board[1][0] == this->board[2][0]) {
            return true;
        }

        return false; // No win detected
    }
    bool is_draw() override {
        return false; // Game is not a draw
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }


private:
    void initialize_pyramid() {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if ((i == 0 && j == 0) || (i == 1 && (j == 0 || j == 1 || j == 2)) || (i == 2 && j < 5)) {
                    this->board[i][j] = ' '; // Valid positions start as empty
                } else {
                    this->board[i][j] = '/'; // Invalid positions
                }
            }
        }
    }
};
#include "minmaxplayer.h"

template <typename T>
class minplayer : public X_O_MinMax_Player<T> {
public:
    minplayer(T symbol) : X_O_MinMax_Player<T>(symbol) {}

    void getmove(int& x, int& y) override {
        this->X_O_MinMax_Player<T>::getmove(x, y);
    }
};

// template <typename T>
// class pyramid_Player : public Player<char> {
// public:
//     pyramid_Player<char>(string name, T symbol) : Player<char>(symbol) {}
//     void getmove(int &x, int &y);
// };

#endif //_PYRAMID_H
