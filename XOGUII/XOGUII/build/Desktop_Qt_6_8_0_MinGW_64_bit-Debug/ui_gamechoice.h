/********************************************************************************
** Form generated from reading UI file 'gamechoice.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMECHOICE_H
#define UI_GAMECHOICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameChoice
{
public:
    QWidget *centralwidget;
    QLabel *choose;

    void setupUi(QMainWindow *GameChoice)
    {
        if (GameChoice->objectName().isEmpty())
            GameChoice->setObjectName("GameChoice");
        GameChoice->resize(800, 600);
        centralwidget = new QWidget(GameChoice);
        centralwidget->setObjectName("centralwidget");
        choose = new QLabel(centralwidget);
        choose->setObjectName("choose");
        choose->setGeometry(QRect(410, 270, 63, 20));
        GameChoice->setCentralWidget(centralwidget);

        retranslateUi(GameChoice);

        QMetaObject::connectSlotsByName(GameChoice);
    } // setupUi

    void retranslateUi(QMainWindow *GameChoice)
    {
        GameChoice->setWindowTitle(QCoreApplication::translate("GameChoice", "MainWindow", nullptr));
        choose->setText(QCoreApplication::translate("GameChoice", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameChoice: public Ui_GameChoice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMECHOICE_H
