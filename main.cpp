#include <iostream>
#include "RTicTacTo.h"
#include "5X5O.h"
#include "ultimateTicTacToe.h" // Include the ulti class
#include "wordTic.h"
#include "BoardGame_Classes.h"
#include "pyramid.h"
using namespace std;

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

    switch (choice) {
        case 1:
            players[1] = new X_O_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new X_O_Random_Player<char>('O');
            break;
        case 3:
            players[1] = new X_O_MinMax_Player<char>('O');
            break;
    }

    // Pick game
    cout << "Enter Game To Play: " << endl;
    cout << "1. Reversed 3x3 Tic-Tac-Toe" << endl;
    cout << "2. 5x5 Tic-Tac-Toe" << endl;
    cout << "3. Pyramid Tic-Tac-Toe" << endl;
    cout << "4. Word Tic-Tac-Toe" << endl;
    cout << "5. Ultimate Tic-Tac-Toe" << endl; // Add Ultimate Tic-Tac-Toe option

    while (true) { // Loop until valid choice is made
        cin >> choiceOfGame;
        if (choiceOfGame >= 1 && choiceOfGame <= 5) break; // Valid choice
        cout << "Invalid choice. Please choose again: ";
    }

    switch (choiceOfGame) {
        case 1:
            B = new RTicTacTo<char>();
            break;
        case 2:
            B = new X_O_Board_5x5<char>();
            break;
        case 3:
            B = new Pyramid<char>();
            break;
        case 4:
            B = new WordTic<char>();
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
