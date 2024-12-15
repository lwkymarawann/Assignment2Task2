#ifndef ULTIMATETICTACTOE_H
#define ULTIMATETICTACTOE_H
#include "BoardGame_Classes.h"
#include "3x3X_O.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

template <typename T>
class ulti : public Board<T> {
private:
    std::vector<std::vector<X_O_Board<char>>> bigBoard;
    int currentSubBoard;

public:
    ulti<char>() {
        bigBoard.resize(3, std::vector<X_O_Board<char>>(3));
        currentSubBoard = -1;
    }

    bool update_board(int z, int x, int y, char symbol) {
        if (z < 0 || z >= 9 || x < 0 || x >= 3 || y < 0 || y >= 3) {
            return false;
        }
        int boardRow = z / 3;
        int boardCol = z % 3;
        return bigBoard[boardRow][boardCol].update_board(x, y, symbol);
    }

    void display_board() override {
        for (int i = 0; i < 3; i++) {
            for (int x = 0; x < 3; x++) {
                for (int j = 0; j < 3; j++) {
                    for (int y = 0; y < 3; y++) {
                        // std::cout << bigBoard[i][j].get_cell(x, y) << " ";
                    }
                    std::cout << "| ";
                }
                std::cout << std::endl;
            }
            std::cout << "-------------------------" << std::endl;
        }
    }

    bool is_win() override {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (bigBoard[i][j].is_win()) {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_draw() override {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (!bigBoard[i][j].is_draw()) {
                    return false;
                }
            }
        }
        return true;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class ulti_random_player : public RandomPlayer<T> {
public:
    ulti_random_player(char symbol) : RandomPlayer<T>(symbol) {}

    void getmove(int& z, int& x, int& y)  {
        srand(time(nullptr));
        z = rand() % 9;
        x = rand() % 3;
        y = rand() % 3;
    }
};

template <typename T>
class ulti_player : public Player<T> {
public:
    ulti_player(std::string name, char symbol) : Player<T>(name, symbol) {}

    void getmove(int& z, int& x, int& y)  {
        std::cout << "Player " << this->name << std::endl;
        std::cout << "Enter the sub-board number (0-8): ";
        std::cin >> z;
        std::cout << "Enter row and column (0-2) for position: ";
        std::cin >> x >> y;
    }
};

#endif // ULTIMATETICTACTOE_H
