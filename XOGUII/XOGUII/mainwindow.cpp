#include "mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIcon>
#include "gamechoice.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("X O Game");
    resize(800, 600);  // Initial size

    // Create buttons and other UI components
    button1 = new QPushButton("Play Game", this);
    button2 = new QPushButton("Quit", this);
    button3 = new QPushButton("Back", this);
    label = new QLabel(this);
    labell = new QLabel(this);
    text = new QLineEdit(this);

    // Setup label with an image
    label->setStyleSheet("background-image: url(:/images/icon.png);"
                         "background-position: center; background-repeat: no-repeat; background-size: cover;");
    label->setFixedSize(329, 352);
    label->setScaledContents(true);
    labell->setStyleSheet("font-weight: bold; font-size: 24px;");

    // Setup text input field
    text->setFixedSize(574, 66);
    text->hide();
    text->setStyleSheet("background: #232635; border: 4px solid #40424C; border-radius:20px; font-weight: bold; font-size: 18px;");

    // Setup buttons
    button1->setStyleSheet("QPushButton { background-color: #E6AF2E; color: white; border-style: solid; border-width: 4px; border-radius: 20px; border-color:#B78615 }"
                           "QPushButton:hover { background-color: #805E0F; color: white; }");
    button2->setStyleSheet("QPushButton { background-color: #E45358; color: white; border-style: solid; border-width: 4px; border-color: #793134; border-radius: 20px; }"
                           "QPushButton:hover { background-color: #D42127; color: white; }");
    button3->setStyleSheet("QPushButton { background-color: #E45358; color: white; border-radius: 20px; border-color:#793134; }"
                           "QPushButton:hover { background-color: #D42127; color: white; }");

    // Hide button3 initially and set its icon
    button3->hide();
    QIcon icon(":/images/backicon.png");
    button3->setIcon(icon);
    button3->setFixedSize(200, 50);

    // Set button sizes
    button1->setFixedSize(300, 50);
    button2->setFixedSize(300, 50);

    // Layout setup
    QVBoxLayout *layout = new QVBoxLayout;

    // Spacer item to add centering effect
    layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Add widgets to layout
    layout->addWidget(label, 0, Qt::AlignCenter);  // Center label
    layout->addWidget(labell, 0, Qt::AlignCenter); // Center labell
    layout->addWidget(text, 0, Qt::AlignCenter);   // Center text field
    layout->addWidget(button1, 0, Qt::AlignCenter); // Center button1
    layout->addWidget(button2, 0, Qt::AlignCenter); // Center button2
    layout->addWidget(button3, 0, Qt::AlignCenter); // Center button3
    text->setAlignment(Qt::AlignCenter);
    // Add spacer item at the bottom to keep the layout centered vertically
    layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Set central widget and layout
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Set cursor to pointing hand for buttons
    button1->setCursor(Qt::PointingHandCursor);
    button2->setCursor(Qt::PointingHandCursor);
    button3->setCursor(Qt::PointingHandCursor);

    // Connect button signals to appropriate slots
    connect(button1, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(button2, &QPushButton::clicked, this, &MainWindow::close);
}


MainWindow::~MainWindow() {}

void MainWindow::startGame() {
    disconnect(button2, &QPushButton::clicked, this, &MainWindow::close);
    disconnect(button1, &QPushButton::clicked, this, &MainWindow::startGame);
    disconnect(button1, &QPushButton::clicked,this, &MainWindow::setName);
    labell->setText("Select Game Mode");
    button1->setText("1 Player");
    button2->setText("2 Players");
    text->hide();
    connect(button1, &QPushButton::clicked, this, &MainWindow::onePlayer);
}

void MainWindow::onePlayer() {
    labell->setText("Enter Player 1's Name");
    button1->setText("Done");
    button2->setText("Back");
    text->show();
    connect(button1, &QPushButton::clicked, this, &MainWindow::setName);
    connect(button2, &QPushButton::clicked, this, &MainWindow::startGame);
}

void MainWindow::setName() {
    name = text->text();
    this->close();
    gamechoice = new GameChoice(this);  // Create new GameChoice window
    gamechoice->exec();  // Show it as a modal dialog
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), backgroundColor);
    QPixmap background(":/images/background.jpg");
    painter.drawPixmap(0, 0, width(), height(), background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    QMainWindow::paintEvent(event);
}
