#ifndef WORDTIC_H
#define WORDTIC_H

#include <iostream>
#include "boardgame_classes.h"
#include "minmaxplayer.h"
#include <fstream>
#include <unordered_set>
#include <string>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

class WordTicPlayer : public Player<char> {
public:
    WordTicPlayer(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << "\nPlease enter your move x and y (0 to 2) followed by the letter you'd like to play: ";
        cin >> x >> y >> this->symbol;
        this->symbol = toupper(this->symbol);
    }

    void setBoard(Board<char>* b) {
        this->boardPtr = b;
    }

private:
    Board<char>* boardPtr; // Pointer to the board for move validation
};

class WordTicRandomPlayer : public Player<char> {
public:
    WordTicRandomPlayer(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int &x, int &y) {
        // Generate a random row between 0 and 2
        x = rand() % 3;
        // Generate a random column between 0 and 2
        y = rand() % 3;
        // Generate a random letter (A-Z)
        this->symbol = 'A' + (rand() % 26);
        std::cout << getname() << " chooses position (" << x << ", " << y << ") and chose the letter " << this->symbol << std::endl;
    }
};

template <typename T>
class WordTic : public Board<char> {
private:
    WordTicPlayer player1;
    WordTicRandomPlayer player2;

public:
    WordTic() : player1("Player 1", 'X'), player2("Player 2", 'O') {
        this->rows = 3;
        this->columns = 3;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns];
        }
        initializeboard();
        player1.setBoard(this);
        player2.setBoard(this);
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
        unordered_set<string> dictionary;
        ifstream file("D://OOP//Assignment Demo//dic.txt");
        if (file.is_open()) {
            string word;
            while (getline(file, word)) {
                if (word.length() == 3) {
                    dictionary.insert(word);
                }
            }
            file.close();
        } else {
            cerr << "Error: Could not open dic.txt\n";
            return false;
        }

        // Check rows, columns, and diagonals
        for (int i = 0; i < 3; ++i) {
            // Check row
            string row_word = {this->board[i][0], this->board[i][1], this->board[i][2]};
            if (dictionary.find(row_word) != dictionary.end()) {
                return true;
            }

            // Check column
            string col_word = {this->board[0][i], this->board[1][i], this->board[2][i]};
            if (dictionary.find(col_word) != dictionary.end()) {
                return true;
            }
        }

        // Check diagonals
        string diag1 = {this->board[0][0], this->board[1][1], this->board[2][2]};
        string diag2 = {this->board[0][2], this->board[1][1], this->board[2][0]};
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

    bool isValidMove(int x, int y) {
        return (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ');
    }
};

#endif //WORDTIC_H
