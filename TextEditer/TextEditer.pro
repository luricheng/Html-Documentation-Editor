#-------------------------------------------------
#
# Project created by QtCreator 2017-01-31T22:23:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextEditer
TEMPLATE = app


SOURCES += main.cpp\
        textediter.cpp \
    file.cpp \
    textformat.cpp \
    findorrepalce.cpp

HEADERS  += textediter.h \
    findorrepalce.h

FORMS    += textediter.ui \
    findorrepalce.ui
