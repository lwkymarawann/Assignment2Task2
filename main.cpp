#include <iostream>
#include "BoardGame_Classes.h"
#include "ultimateTicTacToe.h"
#include "3x3X_O.h"
#include "pyramid.h"
#include "wordTic.h"
using namespace std;


// Concrete implementation of Player
class ulti_player : public Player<char> {
public:
    ulti_player(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int &x, int &y) override {
        cout << getname() << " (" << getsymbol() << "), enter your move (row and column): ";
        cin >> x >> y;
    }
};

class ulti_random_player : public Player<char> {
public:
    ulti_random_player(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int &x, int &y) override {
        x = rand() % 9;  // Generate a random row between 0 and 8
        y = rand() % 9;  // Generate a random column between 0 and 8
        cout << getname() << " chooses position (" << x << ", " << y << ")" << endl;
    }
};

int main() {
    int choice;
    int choiceOfGame;
    Player<char>* players[2];
    Board<char>* B = nullptr; // Initialize B to nullptr
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";

    while (true) { // Loop until valid choice is made
        cin >> choice;
        if (choice >= 1 && choice <= 3) break; // Valid choice
        cout << "Invalid choice. Please choose again: ";
    }

    switch (choice) {
        case 1:
            players[0] = new X_O_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new X_O_Random_Player<char>('X');
            break;
        case 3:
            players[0] = new X_O_MinMax_Player<char>('X');
            players[0]->setBoard(B);
            break;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";

    while (true) { // Loop until valid choice is made
        cin >> choice;
        if (choice >= 1 && choice <= 3) break; // Valid choice
        cout << "Invalid choice. Please choose again: ";
    }

    // Pick game
    cout << "Enter Game To Play: " << endl;
    cout << "1. Pyramid Tic-Tac-Toe" << endl;
    cout << "2. Word Tic-Tac-Toe" << endl;
    cout << "3. Ultimate Tic-Tac-Toe" << endl; // Added new choice

    while (true) { // Loop until valid choice is made
        cin >> choiceOfGame;
        if (choiceOfGame >= 1 && choiceOfGame <= 3) break; // Valid choice
    }

    switch (choiceOfGame) {
        case 1:
            B = new Pyramid<char>();
            break;
        case 2:
            B = new WordTic<char>();
            break;
        case 3: // New case for Ultimate Tic-Tac-Toe
            B = new ulti(); // Remove <char>
            break;
    }

    // Assign player 2
    switch (choice) {
        case 1:
            if (choiceOfGame == 3)
                players[1] = new ulti_player(player2Name, 'O'); // Remove <char>
            else if (choiceOfGame == 2)
                players[1] = new WordTicPlayer(player2Name, 'O');
            else
                players[1] = new X_O_Player<char>(player2Name, 'O'); // Default X-O player
            break;
        case 2:
            if (choiceOfGame == 3)
                players[1] = new ulti_random_player(player2Name, 'O'); // Provide player2Name
            else if (choiceOfGame == 2) {
                players[0] = new WordTicPlayer(playerXName, 'X');
                players[1] = new WordTicRandomPlayer(player2Name, 'O');
            }
            else
                players[1] = new X_O_Random_Player<char>('O');
            break;
        case 3:
            players[1] = new X_O_MinMax_Player<char>('O');
            players[1]->setBoard(B);
            break;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
