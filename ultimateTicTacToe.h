#ifndef ULTIMATETICTACTOE_H
#define ULTIMATETICTACTOE_H

#include <iostream>
#include <vector>
#include "BoardGame_Classes.h"

using namespace std;

// Small 3x3 board class
class SmallBoard : public Board<char> {
private:
    vector<vector<char>> grid;
public:
    SmallBoard() {
        rows = 3;
        columns = 3;
        grid = vector<vector<char>>(3, vector<char>(3, ' '));
    }

    bool update_board(int x, int y, char symbol) override {
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && grid[x][y] == ' ') {
            grid[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << " _________\n";
        for (int i = 0; i < 3; ++i) {
            cout << "|";
            for (int j = 0; j < 3; ++j) {
                cout << "_" << grid[i][j] << "_";
                if (j < 2) cout << "|";
            }
            cout << "|\n";
        }
    }

    bool is_win() override {
        for (int i = 0; i < 3; ++i) {
            if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) return true;
            if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) return true;
        }
        if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) return true;
        if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) return true;
        return false;
    }

    bool is_draw() override {
        return n_moves == 9 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    char get_winner() {
        return is_win() ? grid[1][1] : ' ';
    }

    const vector<vector<char>>& get_grid() const {
        return grid;
    }
};

// Ultimate Tic-Tac-Toe class
class ulti : public Board<char> {
private:
    vector<vector<SmallBoard>> bigGrid;
    vector<vector<char>> winners;
public:
    ulti() {
        rows = 3;
        columns = 3;
        bigGrid = vector<vector<SmallBoard>>(3, vector<SmallBoard>(3));
        winners = vector<vector<char>>(3, vector<char>(3, ' '));
    }

    bool update_board(int x, int y, char symbol) override {
        int bigX = x / 3, bigY = y / 3;
        int smallX = x % 3, smallY = y % 3;

        if (bigX < 3 && bigY < 3 && winners[bigX][bigY] == ' ' &&
            bigGrid[bigX][bigY].update_board(smallX, smallY, symbol)) {
            if (bigGrid[bigX][bigY].is_win()) {
                winners[bigX][bigY] = symbol;
                n_moves++;
            }
            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < 3; ++i) {
            for (int smallRow = 0; smallRow < 3; ++smallRow) {
                for (int j = 0; j < 3; ++j) {
                    if (winners[i][j] != ' ') {
                        cout << "|__" << winners[i][j] << "__|";
                    } else {
                        for (int smallCol = 0; smallCol < 3; ++smallCol) {
                            cout << "|_" << bigGrid[i][j].get_grid()[smallRow][smallCol] << "_|";
                        }
                    }
                    if (j < 2) cout << " || ";
                }
                cout << endl;
            }
            if (i < 2) cout << "====================" << endl;
        }
    }

    bool is_win() override {
        for (int i = 0; i < 3; ++i) {
            if (winners[i][0] != ' ' && winners[i][0] == winners[i][1] && winners[i][1] == winners[i][2]) return true;
            if (winners[0][i] != ' ' && winners[0][i] == winners[1][i] && winners[1][i] == winners[2][i]) return true;
        }
        if (winners[0][0] != ' ' && winners[0][0] == winners[1][1] && winners[1][1] == winners[2][2]) return true;
        if (winners[0][2] != ' ' && winners[0][2] == winners[1][1] && winners[1][1] == winners[2][0]) return true;
        return false;
    }

    bool is_draw() override {
        return n_moves == 9 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

#endif // ULTIMATETICTACTOE_H
