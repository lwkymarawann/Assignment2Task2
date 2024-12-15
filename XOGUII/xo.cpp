#include "xo.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QSpacerItem>
#include <QIcon>
#include "mainwindow.h"
XO::XO(int x,QString z, QWidget *parent)
    : QDialog(parent) , gameParameter(x), name(z) // Initialize QDialog with optional parent
{


    int Symbol = 1; // set it to x by default
    setWindowTitle("Character Choice");
    resize(1920, 1080);  // Set size
    this->showMaximized();  // Maximize the window
    setStyleSheet("background-color:#232635");

    //mainwindow object
    MainWindow *main = new MainWindow();

    // Back button
    backbtn = new QPushButton("Back", this);
    backbtn->setFixedSize(150, 50);
    backbtn->setStyleSheet(
        "QPushButton { "
        "    background-color: #E45358; "
        "    color: white; "
        "    border-style: solid; "
        "    border-width: 4px; "
        "    border-color: #793134; "
        "    border-radius: 20px; "
        "}"
        "QPushButton:hover { "
        "    background-color: #D42127; "
        "    color: white; "
        "}"
        );
    QIcon icon(":/images/backicon.png");
    backbtn->setIcon(icon);
    backbtn->setCursor(Qt::PointingHandCursor);

    // Label for 'OR'
    label = new QLabel("OR", this);
    label->setStyleSheet(
        "background-color: transparent;"
        "font-size: 74px;"
        "font-weight: 600;"
        );

    // Buttons for 'X' and 'O'
    push = new QPushButton("X", this);
    push->setStyleSheet(
        "QPushButton {"
        "    color: #FF5A5F; "
        "    font-weight: bold; "
        "    font-size: 54px; "
        "    background-color: transparent; "
        "    border-radius: 4px; "
        "    border-width: 6px; "
        "    border-style: solid; "
        "    border-color: #E45358;"
        "} "
        "QPushButton:hover { "
        "    background-color: #FF5A5F; "
        "    color: white; "
        "}"
        );

    push1 = new QPushButton("O", this);
    push1->setStyleSheet(
        "QPushButton {"
        "    color: #E6AF2E; "
        "    font-weight: bold; "
        "    font-size: 54px; "
        "    background-color: transparent; "
        "    border-radius: 4px; "
        "    border-width: 6px; "
        "    border-style: solid; "
        "    border-color: #E0AB2E;"
        "} "
        "QPushButton:hover { "
        "    background-color: #E6AF2E; "
        "    color: white; "
        "}"
        );

    // Labels for 'Choose the board'
    choose = new QLabel(this);
    choose->setStyleSheet("background-color:#AE58C6; font-weight: 600; font-size: 26px;");
    choose->setText(" Choose ");
    choose->setFixedSize(90, 45);
    choose->setAlignment(Qt::AlignCenter);

    your = new QLabel(this);
    your->setStyleSheet("background-color:#E45358; font-weight: 600; font-size: 26px;");
    your->setText(" Your ");
    your->setFixedSize(50, 45);
    your->setAlignment(Qt::AlignCenter);

    symbol = new QLabel(this);
    symbol->setStyleSheet("background-color:#48ACFF; font-weight: 600; font-size: 26px;");
    symbol->setText(" Symbol ");
    symbol->setFixedSize(90, 45);
    symbol->setAlignment(Qt::AlignCenter);

    // Set button sizes and cursor
    push->setFixedSize(150, 150);
    push->setCursor(Qt::PointingHandCursor);
    push1->setFixedSize(150, 150);
    push1->setCursor(Qt::PointingHandCursor);

    // Spacers for layout management
    QSpacerItem *leftSpacer = new QSpacerItem(450, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);
    QSpacerItem *rightSpacer = new QSpacerItem(750, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);
    QSpacerItem *leftSpace = new QSpacerItem(300, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);
    QSpacerItem *rightSpace = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Layout for the top row: Back Button + Labels (Choose, Your, Symbol)
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(backbtn);  // Add back button to the left side
    topLayout->addSpacerItem(leftSpacer);  // Add left spacer to balance layout
    topLayout->addWidget(choose);
    topLayout->addWidget(your);
    topLayout->addWidget(symbol);
    topLayout->addSpacerItem(rightSpacer);  // Right spacer

    // Layout for the button and "OR" label
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addSpacerItem(leftSpace);  // Add left spacer
    buttonLayout->addWidget(push, 0, Qt::AlignCenter);  // Center "X" button
    buttonLayout->addWidget(label, 0, Qt::AlignCenter);  // Add "OR" label
    buttonLayout->addWidget(push1, 0, Qt::AlignCenter);  // Center "O" button
    buttonLayout->addSpacerItem(rightSpace);  // Right spacer

    // Add the layouts to the main layout
    mainLayout->addLayout(topLayout);  // Add top layout (back button + labels)
    mainLayout->addLayout(buttonLayout);  // Add button row (X, OR, O)

    // Set the layout for the dialog
    setLayout(mainLayout);

    // Connect the back button to the onBackBtnClicked method
    connect(backbtn, &QPushButton::clicked, this, &XO::onBackBtnClicked);
    connect(push, &QPushButton::clicked, this, XO::onPushClicked);
    connect(push1, &QPushButton::clicked, this, XO::onPush1Clicked);
}

void XO::onPushClicked(){
    this->close();
    ulti = new game(name, gameParameter, 'X');
    ulti->exec();
}

void XO::onPush1Clicked(){
    this->close();
    sus = new game(name, gameParameter, 'O');
    sus->exec();
}
void XO::onBackBtnClicked() {
    this->close();
    MainWindow *main1 = new MainWindow();
    main1->showFullScreen();  // Show the parent widget
}
