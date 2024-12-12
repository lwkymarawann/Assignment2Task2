// GameChoice.cpp
#include "gamechoice.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>  // Include QHBoxLayout for horizontal arrangement
#include <QLabel>  // Include QLabel header for the choose label
#include <QSpacerItem>  // Include QSpacerItem for spacing
#include <QPropertyAnimation>  // Include QPropertyAnimation for animations
#include <QGraphicsOpacityEffect>  // Include for opacity effect

GameChoice::GameChoice(QWidget *parent)
    : QDialog(parent)  // Use QDialog constructor
{
    setWindowTitle("Game Choice");
    resize(1920, 1080);
    this->showMaximized();
    setStyleSheet("background-color:#232635");


    // Create and initialize the game buttons
    game1 = new QPushButton("", this);
    game1->setStyleSheet("font-weight: bold; font-size:24px; background-color:#232635; border-color:#E0AB2E; border-style: solid; border-width: 3px; border-radius: 3px; background-position: center; background-repeat: no-repeat; text-align: center;");
    game1->setFixedSize(500, 700);
    game1->raise();
    QPixmap pixmap1(":/images/game1.png");
    QPixmap scaledPixmap1 = pixmap1.scaled(game1->size() *0.9, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    game1->setIcon(scaledPixmap1);
    game1->setIconSize(game1->size());
    game1Label = new QLabel("ULTIMATE TIC-TAC-TOE", game1); // Set parent to game1
    game1Label->setAlignment(Qt::AlignCenter);
    game1Label->setStyleSheet("color: #E6AF2E; font-size: 34px;border-style: none; background: transparent; font-weight: bold; background-color: transparent;");

    game2 = new QPushButton("", this);
    game2->setStyleSheet("font-weight: bold; font-size:24px; background-color:#232635; border-color:#E0AB2E; border-style: solid; border-width: 3px; border-radius: 3px; background-position: center; background-repeat: no-repeat; text-align: center;");
    game2->setFixedSize(540, 700);
    game2->raise();
    QPixmap pixmap2(":/images/game2.png");
    QPixmap scaledPixmap2 = pixmap2.scaled(game2->size() * 0.9, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    game2->setIcon(scaledPixmap2);
    game2->setIconSize(game2->size());
    game2Label = new QLabel("SUS TIC-TAC-TOE", game2); // Set parent to game2
    game2Label->setAlignment(Qt::AlignCenter);
    game2Label->setStyleSheet("color: #E6AF2E;border-style: none; font-size: 34px;background: transparent; font-weight: bold; background-color: transparent;");


    game1Label->setGeometry(0, game1->height() / 2 +230, game1->width(), 50); // Center label vertically
    game2Label->setGeometry(0, game2->height() / 2 + 230, game2->width(), 50); // Center label vertically
    // Create and initialize the 'choose' label
    choose = new QLabel(this);
    choose->setStyleSheet("background-color:#AE58C6; font-weight: 600; font-size: 26px;");
    choose->setText("Choose ");
    choose->setFixedSize(90, 45);
    choose->setAlignment(Qt::AlignCenter);  // Align text inside the label to center

    the = new QLabel(this);
    the->setStyleSheet("background-color:#E45358; font-weight: 600; font-size: 26px;");
    the->setText("the ");
    the->setFixedSize(50, 45);
    the->setAlignment(Qt::AlignCenter);  // Align text inside the label to center

    board = new QLabel(this);
    board->setStyleSheet("background-color:#48ACFF; font-weight: 600; font-size: 26px;");
    board->setText("board ");
    board->setFixedSize(90, 45);
    board->setAlignment(Qt::AlignCenter);  // Align text inside the label to center

    game = new QLabel(this);
    game->setStyleSheet("background-color:#E6AF2EF7; font-weight: 600; font-size: 26px;");
    game->setText("game ");
    game->setFixedSize(90, 45);
    game->setAlignment(Qt::AlignCenter);  // Align text inside the label to center

    // Create the backButton
    backButton = new QPushButton("Back", this);
    backButton->setFixedSize(150, 50);
    backButton->setStyleSheet("QPushButton { background-color: #E45358; color: white; border-style: solid; border-width: 4px; border-color: #793134; border-radius: 20px; }"
                              "QPushButton:hover { background-color: #D42127; color: white; }");

    // Set the icon for the back button
    QIcon icon(":/images/backicon.png");
    backButton->setIcon(icon);

    // Create horizontal spacers
    QSpacerItem* leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);  // Left spacer
    QSpacerItem* rightSpacer = new QSpacerItem(600, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);  // Right spacer

    // Create the horizontal layout for the labels
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(backButton);  // Add backButton first (top-left)
    topLayout->addItem(leftSpacer);    // Left spacer to push backButton to the left
    topLayout->addWidget(choose);
    topLayout->addWidget(the);
    topLayout->addWidget(board);
    topLayout->addWidget(game);
    topLayout->addItem(rightSpacer);   // Right spacer to push the labels to the center
    topLayout->setAlignment(Qt::AlignTop);  // Align labels at the top (no need to center them here, as spacers handle that)
    QSpacerItem* rightSpacer1 = new QSpacerItem(150, 0, QSizePolicy::Maximum, QSizePolicy::Minimum);
    QSpacerItem* leftSpacer1 = new QSpacerItem(130, 0, QSizePolicy::Maximum, QSizePolicy::Minimum);  // Left spacer

    QHBoxLayout *sideLayout = new QHBoxLayout;
    sideLayout->addItem(leftSpacer1);
    sideLayout->addWidget(game1, 0, Qt::AlignLeft | Qt::AlignCenter);
    sideLayout->addWidget(game2, 0, Qt::AlignRight | Qt::AlignCenter);
    sideLayout->addItem(rightSpacer1);

    // Create the main layout and add the horizontal layout for labels
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);  // Add the topLayout (labels) horizontally
    mainLayout->addLayout(sideLayout);
    setLayout(mainLayout);

    // Set cursor for backButton
    backButton->setCursor(Qt::PointingHandCursor);
    game1->setCursor(Qt::PointingHandCursor);
    game2->setCursor(Qt::PointingHandCursor);

    // Connect the back button to the onBackButtonClicked slot
    connect(backButton, &QPushButton::clicked, this, &GameChoice::onBackButtonClicked);

    createHoverAnimation(game1, game1Label);
    createHoverAnimation(game2, game2Label);

}

void GameChoice::createHoverAnimation(QPushButton *button, QLabel *label) {
    button->installEventFilter(this);  // Install event filter for the button
}

bool GameChoice::eventFilter(QObject *obj, QEvent *event) {
    QPushButton *button = qobject_cast<QPushButton *>(obj);
    if (!button) return QDialog::eventFilter(obj, event); // Pass unhandled events to parent

    QLabel *associatedLabel = nullptr;
    QPixmap originalPixmap;

    if (button == game1) {
        associatedLabel = game1Label;
        originalPixmap = QPixmap(":/images/game1.png"); // Load original pixmap for scaling
    } else if (button == game2) {
        associatedLabel = game2Label;
        originalPixmap = QPixmap(":/images/game2.png"); // Load original pixmap for scaling
    }

    if (associatedLabel && (event->type() == QEvent::Enter || event->type() == QEvent::Leave)) {
        // Create icon animation
        QPropertyAnimation *iconAnimation = new QPropertyAnimation(button, "iconSize");
        iconAnimation->setDuration(200); // Set duration for the animation
        QSize scaledSize = button->iconSize() * 1.2;
        QSize originalSize = button->size() * 0.8;
        button->iconSize() = button->iconSize() *0.8;
        if (event->type() == QEvent::Enter) {
            // Scale icon to 1.2x
            iconAnimation->setStartValue(originalSize);
            iconAnimation->setEndValue(scaledSize);
        } else if (event->type() == QEvent::Leave) {
            // Reset icon to original size
            iconAnimation->setStartValue(scaledSize);
            iconAnimation->setEndValue(originalSize); // Replace with your original icon size
        }

        // Start the icon animation
        iconAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        // Create label animation
        QPropertyAnimation *labelAnimation = new QPropertyAnimation(associatedLabel, "geometry");
        labelAnimation->setDuration(300); // 200 ms for smooth transition

        QRect startGeometry = associatedLabel->geometry();
        QRect endGeometry = startGeometry;

        if (event->type() == QEvent::Enter) {
            // Move label to the top of the associated button
            endGeometry.moveTop(startGeometry.top() - 510);
        } else if (event->type() == QEvent::Leave) {

            // Move label back to its initial centered position
            int centerY = (button->height() / 2) + 230; // Calculate center Y position
            endGeometry.moveTop(centerY); // Return label to center
        }

        labelAnimation->setStartValue(startGeometry);
        labelAnimation->setEndValue(endGeometry);
        labelAnimation->setEasingCurve(QEasingCurve::InOutQuad); // Smooth easing curve
        labelAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        return true; // Event handled
    }
    return QDialog::eventFilter(obj, event); // Pass unhandled events to parent
}


void GameChoice::onBackButtonClicked() {
    this->close();
    parentWidget()->show();  // This will show the parent (MainWindow)
}

GameChoice::~GameChoice() {
    // Destructor code, if necessary
}
