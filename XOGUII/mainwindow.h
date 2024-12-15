#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QColor>
#include "gamechoice.h"
#include "xo.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString p_name();

private:
    void handleButtonClick(QPushButton *button);
    void twoPlayers();
    void startGame(); // Add this declaration
    void onePlayer();
    void setName();
    // void showGame();
    void Done();
    int notEmpty = 1;
    QString name;
    QString name2;
    QPushButton *button1;  // Declare button1 as a member variable
    QPushButton *button2;  // Declare button2 as a member variable
    QLabel *label;
    QLabel *labell;
    QLineEdit *text;
    QPushButton *button3;
    QColor backgroundColor;
    GameChoice *gamechoice;
    void launchGame();
    void requestSecondPlayerName();
    void requestPlayerName();
    bool isTwoPlayers;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MAINWINDOW_H
