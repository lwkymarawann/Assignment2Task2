#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QColor>
#include "gamechoice.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void startGame(); // Add this declaration
    void onePlayer();
    void setName();
    // void showGame();
    QPushButton *button1;  // Declare button1 as a member variable
    QPushButton *button2;  // Declare button2 as a member variable
    QLabel *label;
    QLabel *labell;
    QLineEdit *text;
    QString name;
    QPushButton *button3;
    QColor backgroundColor;
    GameChoice *gamechoice;


protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MAINWINDOW_H
