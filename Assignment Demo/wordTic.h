//
// Created by PC on 12/10/2024.
//


#ifndef WORDTIC_H
#define WORDTIC_H

#include <iostream>
#include "boardgame_classes.h"
#include "minmaxplayer.h"
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;


class WordTicPlayer : public Player<char> {
public:
    WordTicPlayer(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << "\nPlease enter your move x and y (0 to 2) followed by the letter you'd like to play separated by spaces: ";
        cin >> x >> y >> this->symbol;
        symbol = toupper(symbol);
    }
    char getsymbol() {
        return symbol;
    };
    void setBoard(Board<char>* b) {
        this->boardPtr = b;
    };


};


template <typename T>
class WordTic : public Board<char> {
private:
    char symbol;
    WordTicPlayer player;
public:
    WordTic() : player("Player 1", 'X') {
        this->rows = 3;
        this->columns = 3;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns];
        }
        initializeboard();
    }





    ~WordTic() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, char symbol) override {
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && this->board[x][y] == ' ') {
            this->board[x][y] = symbol;
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << "___________________" << endl;
        for (int i = 0; i < this->rows; ++i) {
            cout << "|     |     |     |" << endl;
            cout << "|  " << this->board[i][0] << "  |  " << this->board[i][1] << "  |  " << this->board[i][2] << "  |" << endl;
            cout << "|_____|_____|_____|" << endl;
        }
    }

    bool is_win() {
        // Load the dictionary
        std::unordered_set<std::string> dictionary;
        std::ifstream file("D://OOP//Assignment Demo//dic.txt");
        if (file.is_open()) {
            std::string word;
            while (std::getline(file, word)) {
                if (word.length() == 3) {
                    dictionary.insert(word);
                }
            }
            file.close();
        } else {
            std::cerr << "Error: Could not open dic.txt\n";
            return false;
        }

        // Check rows, columns, and diagonals
        for (int i = 0; i < 3; ++i) {
            // Check row
            std::string row_word = {this->board[i][0], this->board[i][1], this->board[i][2]};
            if (dictionary.find(row_word) != dictionary.end()) {
                return true;
            }

            // Check column
            std::string col_word = {this->board[0][i], this->board[1][i], this->board[2][i]};
            if (dictionary.find(col_word) != dictionary.end()) {
                return true;
            }
        }

        // Check diagonals
        std::string diag1 = {this->board[0][0], this->board[1][1], this->board[2][2]};
        std::string diag2 = {this->board[0][2], this->board[1][1], this->board[2][0]};
        if (dictionary.find(diag1) != dictionary.end() || dictionary.find(diag2) != dictionary.end()) {
            return true;
        }

        return false;
    }

    bool is_draw() {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                if (this->board[i][j] == ' ') {
                    return false; // Found an empty space, not a draw
                }
            }
        }
        return !is_win(); // It's a draw if no winning condition is met
    }

    bool game_is_over() {
        return is_win() || is_draw();
    }


    void initializeboard() {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = ' '; // Initialize the board with spaces
            }
        }
    }
};






#endif //WORDTIC_H
