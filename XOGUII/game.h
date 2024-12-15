#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <vector>

class game : public QDialog
{
    Q_OBJECT

public:
    explicit game(QString z, int x, char y, QWidget *parent = nullptr);

private:
    QString name;
    QString winnerSymbol;
    int currentGame;
    char currentPlayer; // 'X' or 'O'
    QLabel *statusLabel; // Status label to display the current player's turn or winner
    QGridLayout *mainGrid; // 3x3 main grid containing sub-grids
    std::vector<std::vector<QGridLayout*>> subGrids; // 3x3 grid of sub-grids
    std::vector<std::vector<std::vector<std::vector<QPushButton*>>>> gridButtons; // Buttons for each cell in each sub-grid
    std::vector<std::vector<char>> bigGridStatus; // Tracks the winner of each sub-grid
    QPushButton *resetButton; // Button to reset the game
    // QLabel *winnerLabel;
    QVector<QPushButton *> buttons;
    QList<QLabel*> winnerLabels;
    void initializeGrid();
    void handleButtonClick(int bigRow, int bigCol, int smallRow, int smallCol);
    bool isMoveValid(int bigRow, int bigCol, int smallRow, int smallCol);
    bool checkSmallGridWin(int bigRow, int bigCol, char player);
    bool checkBigGridWin(char player);
    void replaceWithWinner(int bigRow, int bigCol, char winner);
    void displayWinner(const QString &winnerMessage);
    void resetGame();
    bool checkWinCondition();
    void makeAIMove();
    bool aiThinking;
    bool checkDraw();
    void resetGamee();
    QGridLayout *gridLayout;
    void initializesusGrid();
    bool isPlayerXTurn; // True for Player 1 (S), False for Player 2 (U)
    void handleButtonClickk(QPushButton *button);
    int j;
    int m;
    int n;
    void aiMove();


private:
    int lastBigRow = -1; // To keep track of the last move's big grid row
    int lastBigCol = -1; // To keep track of the last move's big grid column

};

#endif // GAME_H
