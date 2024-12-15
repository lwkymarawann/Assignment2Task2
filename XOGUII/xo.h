#ifndef XO_H
#define XO_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
// #include "mainwindow.h"
// #include "gamechoice.h"
#include "game.h"
class XO : public QDialog
{
    Q_OBJECT

public:
    XO(int x,QString z, QWidget *parent = nullptr); // Constructor with an optional parent widget

private:
    QString name;
    int gameParameter;
    QPushButton *push; // Button pointer
    QPushButton *push1; // Button pointer
    QLabel *label;
    QLabel *choose;
    QLabel *your;
    QLabel *symbol;
    QPushButton *backbtn;
    void onBackBtnClicked();
    void onPushClicked();
    void onPush1Clicked();
    game *ulti;
    game *sus;
};

#endif // XO_H
