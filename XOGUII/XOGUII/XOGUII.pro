QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    gamechoice.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    gamechoice.h \
    mainwindow.h

FORMS += \
    gamechoice.ui \
    mainwindow.ui

RESOURCES += \
    resource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
