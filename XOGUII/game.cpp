#include "game.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFrame>
#include <QTimer>
#include <cstdlib>
#include <ctime>
#include <QFont>
#include <QList>
#include <QRandomGenerator>
game::game(QString z, int x, char y, QWidget *parent)
    : QDialog(parent),name(z), currentGame(x), currentPlayer(y), aiThinking(false)
{


    if(x == 0){
    setWindowTitle("Ultimate Tic Tac Toe");
    resize(1920, 1080);
    setStyleSheet("background-color: #232635;");

    statusLabel = new QLabel("Player X's Turn", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 10px;");

    resetButton = new QPushButton("Reset Game", this);
    resetButton->setStyleSheet("font-size: 18px; background-color: #444; color: white; border: 1px solid #ffffff; border-radius: 5px;");
    connect(resetButton, &QPushButton::clicked, this, &game::resetGame);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(statusLabel);

    mainGrid = new QGridLayout();
    mainGrid->setSpacing(10);
    mainLayout->addLayout(mainGrid);
    mainLayout->addWidget(resetButton, 0, Qt::AlignBottom); // Place reset button at the bottom

    initializeGrid();
    setLayout(mainLayout);
    void initializeGrid();
    void handleButtonClick(int bigRow, int bigCol, int smallRow, int smallCol);
    bool isMoveValid(int bigRow, int bigCol, int smallRow, int smallCol);
    bool checkSmallGridWin(int bigRow, int bigCol, char player);
    bool checkBigGridWin(char player);
    void replaceWithWinner(int bigRow, int bigCol, char winner);
    void displayWinner(const QString &winnerMessage);
    void resetGame();
    void makeAIMove();
    bool checkDraw();
}
    else if (x == 1) {
        gridLayout = new QGridLayout(this);
        setWindowTitle("4x4 Tic-Tac-Toe");
        resize(1920, 1080);
        setStyleSheet("background-color: #; color: white;");
        initializesusGrid();
    }


}
void game::initializeGrid()
{
    subGrids.resize(3, std::vector<QGridLayout*>(3, nullptr));
    gridButtons.resize(3, std::vector<std::vector<std::vector<QPushButton*>>>(3, std::vector<std::vector<QPushButton*>>(3, std::vector<QPushButton*>(3, nullptr))));
    bigGridStatus.resize(3, std::vector<char>(3, '\0'));

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QFrame *frame = new QFrame(this);
            frame->setFrameStyle(QFrame::Box | QFrame::Raised);
            frame->setLineWidth(3);
            frame->setStyleSheet("border: 2px solid #ffffff;");

            QGridLayout *subGrid = new QGridLayout(frame);
            subGrid->setSpacing(5);
            subGrids[i][j] = subGrid;

            for (int m = 0; m < 3; ++m) {
                for (int n = 0; n < 3; ++n) {
                    QPushButton *button = new QPushButton(frame);
                    button->setFixedSize(70, 70);
                    button->setStyleSheet("font-size: 24px; font-weight: bold; "
                                          "background-color: #2e2e3e; color: #ffffff; "
                                          "border: 1px solid #444444; border-radius: 5px;");
                    subGrid->addWidget(button, m, n);
                    button->setCursor(Qt::PointingHandCursor);
                    gridButtons[i][j][m][n] = button;

                    connect(button, &QPushButton::clicked, this, [=]() { handleButtonClick(i, j, m, n); });
                }
            }

            mainGrid->addWidget(frame, i, j);
        }
    }
}

void game::handleButtonClick(int bigRow, int bigCol, int smallRow, int smallCol)
{
    if (aiThinking) return; // Prevent player moves while AI is thinking

    QPushButton *button = gridButtons[bigRow][bigCol][smallRow][smallCol];
    if (button->text().isEmpty()) {
        // Store last player's move
        lastBigRow = bigRow;
        lastBigCol = bigCol;

        button->setText(currentPlayer == 'X' ? "X" : "O");
        button->setStyleSheet(QString("font-size: 24px; font-weight: bold; color: %1; background-color: #444; border: 2px solid %2;")
                                  .arg(currentPlayer == 'X' ? "red" : "yellow")
                                  .arg(currentPlayer == 'X' ? "red" : "yellow"));

        // Check for win in the small grid
        if (checkSmallGridWin(bigRow, bigCol, currentPlayer)) {
            replaceWithWinner(bigRow, bigCol, currentPlayer);
            if (checkBigGridWin(currentPlayer)) {
                displayWinner(QString(name + " Wins!").arg(currentPlayer));
                return;
            }
        }

        // Check for draw
        if (checkDraw()) {
            displayWinner("It's a Draw!");
            return;
        }

        // Switch player and make AI move if current player is X
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        statusLabel->setText(QString("AI Thinking..."));

        if (currentPlayer == 'O') {
            aiThinking = true; // Set AI thinking flag
            QTimer::singleShot(1000, this, &game::makeAIMove); // Simulate AI thinking
        } else {
            statusLabel->setText(QString("Player %1's Turn").arg(currentPlayer));
        }
    }
}

void game::makeAIMove()
{
    // AI makes a random move
    int bigRow, bigCol, smallRow, smallCol;
    srand(static_cast<unsigned>(time(nullptr)));

    do {
        bigRow = rand() % 3;
        bigCol = rand() % 3;
        smallRow = rand() % 3;
        smallCol = rand() % 3;
    } while (!isMoveValid(bigRow, bigCol, smallRow, smallCol)); // Only valid moves

    QPushButton *button = gridButtons[bigRow][bigCol][smallRow][smallCol];
    button->setText("O");
    button->setStyleSheet("font-size: 24px; font-weight: bold; color: yellow; background-color: #444; border: 2px solid yellow;");

    // Check for win in the small grid
    if (checkSmallGridWin(bigRow, bigCol, 'O')) {
        replaceWithWinner(bigRow, bigCol, 'O');
        if (checkBigGridWin('O')) {
            displayWinner(QString("Player O Wins!"));
            return;
        }
    }

    // Check for draw
    if (checkDraw()) {
        displayWinner("It's a Draw!");
        return;
    }

    // Switch back to player X
    currentPlayer = 'X';
    aiThinking = false; // Reset AI thinking flag
    statusLabel->setText(QString("Player %1's Turn").arg(currentPlayer));
}

bool game::isMoveValid(int bigRow, int bigCol, int smallRow, int smallCol)
{
    return gridButtons[bigRow][bigCol][smallRow][smallCol]->text().isEmpty() &&
           bigGridStatus[bigRow][bigCol] == '\0'; // Check if the big box is not won
}

bool game::checkSmallGridWin(int bigRow, int bigCol, char player)
{
    auto &grid = gridButtons[bigRow][bigCol];
    for (int i = 0; i < 3; ++i) {
        if (grid[i][0]->text() == player && grid[i][1]->text() == player && grid[i][2]->text() == player)
            return true;
        if (grid[0][i]->text() == player && grid[1][i]->text() == player && grid[2][i]->text() == player)
            return true;
    }
    return (grid[0][0]->text() == player && grid[1][1]->text() == player && grid[2][2]->text() == player) ||
           (grid[0][2]->text() == player && grid[1][1]->text() == player && grid[2][0]->text() == player);
}

bool game::checkBigGridWin(char player)
{
    for (int i = 0; i < 3; ++i) {
        if (bigGridStatus[i][0] == player && bigGridStatus[i][1] == player && bigGridStatus[i][2] == player)
            return true;
        if (bigGridStatus[0][i] == player && bigGridStatus[1][i] == player && bigGridStatus[2][i] == player)
            return true;
    }
    return (bigGridStatus[0][0] == player && bigGridStatus[1][1] == player && bigGridStatus[2][2] == player) ||
           (bigGridStatus[0][2] == player && bigGridStatus[1][1] == player && bigGridStatus[2][0] == player);
}

void game::replaceWithWinner(int bigRow, int bigCol, char winner)
{
    bigGridStatus[bigRow][bigCol] = winner;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QPushButton *button = gridButtons[bigRow][bigCol][i][j];
            button->setDisabled(true); // Disable the buttons in the winning small grid
        }
    }

    QLabel *winnerLabel = new QLabel(this);
    winnerLabel->setText(winner == 'X' ? QString("X").arg(winner).arg(bigRow + 1).arg(bigCol + 1) :QString("O").arg(winner).arg(bigRow + 1).arg(bigCol + 1)  );
    winnerLabel->setStyleSheet(winner == 'X' ? "border-width: 3px; border-style: solid; font-size: 42px; color: red; border-color: red; font-weight: bold;" : "border-width: 3px; border-style: solid; font-size: 42px; color: yellow; border-color: yellow; font-weight: bold;");
    winnerLabel->setAlignment(Qt::AlignCenter);
    mainGrid->addWidget(winnerLabel, bigRow, bigCol);
    winnerLabels.append(winnerLabel); // Store the label for future reference
}

bool game::checkDraw()
{
    for (const auto &row : bigGridStatus) {
        for (char status : row) {
            if (status == '\0') {
                return false; // Found an empty cell, not a draw
            }
        }
    }
    return true; // No empty cells
}

void game::displayWinner(const QString &message)
{
    QMessageBox::information(this, "Game Over", message);
    resetGame(); // Automatically reset the game after displaying the winner
}

void game::resetGame()
{
    // Clear the big grid statuses
    for (auto &row : bigGridStatus) {
        std::fill(row.begin(), row.end(), '\0');
    }

    // Clear the small grid buttons and winner labels
    for (auto &subGrid : gridButtons) {
        for (auto &smallGrid : subGrid) {
            for (auto &button : smallGrid) {
                for (auto &btn : button) {
                    btn->setText("");
                    btn->setDisabled(false);
                    btn->setStyleSheet("font-size: 24px; font-weight: bold; "
                                       "background-color: #2e2e3e; color: #ffffff; "
                                       "border: 1px solid #444444; border-radius: 5px;");
                }
            }
        }
    }

    // Clear winner labels
    for (QLabel *label : winnerLabels) {
        delete label; // Delete the labels
    }
    winnerLabels.clear(); // Clear the list

    currentPlayer = 'X';
    aiThinking = false; // Reset AI thinking flag
    statusLabel->setText(QString("Player %1's Turn").arg(currentPlayer));
}


void game::initializesusGrid() {

    buttons.clear();
    gridLayout->setSpacing(0);

    for (int i = 0; i < 16; ++i) {
        QPushButton *button = new QPushButton(this);
        button->setFixedSize(100, 100);
        button->setFont(QFont("Arial", 24, QFont::Bold));

        button->setStyleSheet(
            "background-color: #2e3440; "
            "color: white; "
            "border: 2px solid #4c566a; " // Adjust border width and color as needed
            "border-radius: 0px; " // Remove rounded corners
            ""
            );
        button->setCursor(Qt::PointingHandCursor);
        button->setText("");
        buttons.append(button);

        gridLayout->addWidget(button, i / 4, i % 4);

        connect(button, &QPushButton::clicked, this, [=]() {
            handleButtonClickk(button);
        });
    }

    // Set the background color and add the grid layout to the central widget
    setLayout(gridLayout);
}

void game::handleButtonClickk(QPushButton *clickedButton) {
    if (!clickedButton || !clickedButton->text().isEmpty()) {
        return; // Ignore if the button is already pressed
    }

    // Update button text and toggle turn
    clickedButton->setText(QString(currentPlayer)); // Set the text to the current player's symbol (X or O)

    // Set button style depending on the current player
    clickedButton->setStyleSheet(currentPlayer == 'X' ?
                                     "border-radius: 20px; color: red; border-width: 3px; border-style: solid ; border-color: red; background-color: transparent; " :
                                     "border-radius: 20px; border-width: 3px; border-style: solid ; border-color: yellow; color: yellow; border-width: 3px; background-color: transparent; ");

    // Check win condition
    if (checkWinCondition()) {
        QString winner = currentPlayer ? name + " Wins" : "AI Wins";
        QMessageBox::information(this, "Game Over", winner + "!");
        resetGamee();        // Reset the game after showing the message
        return;
    }

    // Switch to AI's turn
    isPlayerXTurn = false;
    QTimer::singleShot(1000, this, &game::aiMove); // Simulate AI thinking time
}

void game::aiMove() {
    // Simple AI logic to find a random empty button
    QList<QPushButton *> emptyButtons;
    for (auto *button : buttons) {
        if (button->text().isEmpty()) {
            emptyButtons.append(button);
        }
    }

    if (!emptyButtons.isEmpty()) {
        // Choose a random button for AI to play
        int randomIndex = QRandomGenerator::global()->bounded(emptyButtons.size());
        QPushButton *aiButton = emptyButtons[randomIndex];

        // AI plays "O"
        aiButton->setText(currentPlayer == 'X' ? "O" : "X");
        aiButton->setStyleSheet(currentPlayer == 'X' ? "border-radius: 20px; border-width: 3px; border-style: solid ; border-color: yellow; color: yellow; border-width: 3px; background-color: transparent; " :
                                "color: red; border-radius: 20px; border-width: 3px; border-style: solid ; border-color: red; background-color: transparent; ");



        // Check win condition after AI's move
        if (checkWinCondition()) {
            QMessageBox::information(this, "Game Over", "AI wins!");
            resetGamee(); // Reset the game after showing the message
            return;
        }
    }

    // Switch back to Player's turn
    isPlayerXTurn = true;
}

bool game::checkWinCondition() {
    // Check for 3 in a row horizontally, vertically, or diagonally
    for (int i = 0; i < 4; ++i) {
        // Check rows for 3 in a row
        for (int j = 0; j < 2; ++j) { // Check columns 0-1, 1-2
            if (buttons[i * 4 + j]->text() == buttons[i * 4 + j + 1]->text() &&
                buttons[i * 4 + j + 1]->text() == buttons[i * 4 + j + 2]->text() &&
                !buttons[i * 4 + j]->text().isEmpty()) {
                winnerSymbol = buttons[i * 4 + j]->text(); // Store winner
                return true;
            }
        }
        // Check columns for 3 in a row
        for (int j = 0; j < 2; ++j) { // Check rows 0-1, 1-2
            if (buttons[j * 4 + i]->text() == buttons[(j + 1) * 4 + i]->text() &&
                buttons[(j + 1) * 4 + i]->text() == buttons[(j + 2) * 4 + i]->text() &&
                !buttons[j * 4 + i]->text().isEmpty()) {
                winnerSymbol = buttons[j * 4 + i]->text(); // Store winner
                return true;
            }
        }
    }

    // Check diagonals for 3 in a row
    if (buttons[0]->text() == buttons[5]->text() && buttons[5]->text() == buttons[10]->text() && !buttons[0]->text().isEmpty()) {
        winnerSymbol = buttons[0]->text(); // Store winner
        return true;
    }
    if (buttons[3]->text() == buttons[6]->text() && buttons[6]->text() == buttons[9]->text() && !buttons[3]->text().isEmpty()) {
        winnerSymbol = buttons[3]->text(); // Store winner
        return true;
    }

    // Additional diagonal checks can go here

    return false; // No winner found
}


void game::resetGamee() {
    for (auto *button : buttons) {
        button->setText("");
        button->setStyleSheet("background-color: #2e3440; color: white; border-radius: 20px;");
    }
    isPlayerXTurn = true; // Reset to Player X's turn // Reset current player to 'X'
    winnerSymbol = ""; // Clear the winner variable
}
