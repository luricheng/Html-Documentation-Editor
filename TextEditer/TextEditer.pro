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

DISTFILES += \
    icons/bold.png \
    icons/center.png \
    icons/color.png \
    icons/copy.png \
    icons/cut.png \
    icons/image.png \
    icons/italic.png \
    icons/justify.png \
    icons/left.png \
    icons/new.png \
    icons/open.png \
    icons/paste.png \
    icons/printImage.png \
    icons/printText.png \
    icons/redo.png \
    icons/right.png \
    icons/rotate90.png \
    icons/rotate180.png \
    icons/rotate270.png \
    icons/underline.png \
    icons/undo.png \
    icons/zoomin.png \
    icons/zoomout.png \
    about \
    help

RESOURCES += \
    icons/icons.qrc
