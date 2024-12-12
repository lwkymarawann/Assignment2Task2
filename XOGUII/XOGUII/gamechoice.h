#ifndef GAMECHOICE_H
#define GAMECHOICE_H

#include <QDialog>  // Include QDialog for modal behavior
#include <QPushButton>
#include <QColor>
#include <QLabel>
#include <QFrame>
#include <QPropertyAnimation>
#include <QEvent>
#include <QVariant>

class GameChoice : public QDialog // Inherit from QWidget to make it a widget
{
    Q_OBJECT  // Required for Qt's signal/slot mechanism

public:
    explicit GameChoice(QWidget *parent = nullptr);  // Constructor accepting a QWidget parent
    ~GameChoice();  // Destructor

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:

    void createHoverAnimation(QPushButton *button,QLabel *label);  // Ensure this matches QLabel, not QPushButton


         // Define buttons, labels, or other widgets you want in this class
    QPushButton *backButton;
    QColor backgroundColor;
    QLabel *choose;
    QLabel *the;
    QLabel *board;
    QLabel *game;
    QPushButton *game1;
    QPushButton * game2;
    QLabel *game1Label;
    QLabel *game2Label;

private slots:
    void onBackButtonClicked();  // Example slot for the "Back" button
};

#endif // GAMECHOICE_H
