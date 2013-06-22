#-------------------------------------------------
#
# Project created by QtCreator 2013-06-18T22:57:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = karnaugh_map
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tabletrue.cpp \
    karnaughmap.cpp \
    searchcoating.cpp \
    gminifunction.cpp

HEADERS  += mainwindow.h \
    tabletrue.h \
    karnaughmap.h \
    searchcoating.h \
    gminifunction.h

FORMS    += mainwindow.ui
