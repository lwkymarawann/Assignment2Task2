#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/app_icon.jpg"));

    MainWindow w;
    w.showMaximized();

    return app.exec();
}
