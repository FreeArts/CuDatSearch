#-------------------------------------------------
#
# Project created by QtCreator 2019-03-02T11:03:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CuDatSearch
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    csvreader.cpp

HEADERS += \
        mainwindow.h \
    csvreader.h

FORMS += \
        mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../CuDatBase/cudatbase/src/ -lSelect
unix:!macx: LIBS += -L$$PWD/../CuDatBase/cudatbase/src/ -lCudaSelect

INCLUDEPATH += $$PWD/../CuDatBase/cudatbase/src
DEPENDPATH += $$PWD/../CuDatBase/cudatbase/src


unix:!macx: LIBS += -lcudart
#Maybe not needed :
unix:!macx: LIBS += -lcuda

