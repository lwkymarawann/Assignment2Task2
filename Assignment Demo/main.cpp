#include <iostream>
#include "BoardGame_Classes.h"
#include "MinMaxPlayer.h"
#include "3x3x_o.h"
#include "pyramid.h"
#include "wordtic.h"

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

    while (true) { // Loop until valid choice is made
        cin >> choiceOfGame;
        if (choiceOfGame == 1 || choiceOfGame == 2) break; // Valid choice
        cout << "Invalid choice. Please choose again: ";
    }

    switch (choiceOfGame) {
        case 1:
            B = new Pyramid<char>();
            switch (choice) {
                case 1:
                    players[1] = new X_O_Player<char>(player2Name, 'O'); // Use a concrete class
                break;
                case 2:
                    players[1] = new X_O_Random_Player<char>('O');
                break;
                case 3:
                    players[1] = new X_O_MinMax_Player<char>('O');
                players[1]->setBoard(B);
                break;
            }
            break;
        case 2:
            B = new WordTic<char>();
            switch (choice) {
                case 1:
                    players[1] = new WordTicPlayer(player2Name, 'O'); // Use a concrete class
                break;
                case 2:
                    players[1] = new X_O_Random_Player<char>('O');
                break;
                case 3:
                    players[1] = new X_O_MinMax_Player<char>('O');
                players[1]->setBoard(B);
                break;
            }
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
