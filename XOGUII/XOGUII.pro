QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    game.cpp \
    gamechoice.cpp \
    main.cpp \
    mainwindow.cpp \
    xo.cpp

HEADERS += \
    game.h \
    gamechoice.h \
    mainwindow.h \
    xo.h

FORMS += \
    gamechoice.ui \
    mainwindow.ui

RESOURCES += \
    resource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
