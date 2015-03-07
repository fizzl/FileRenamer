#-------------------------------------------------
#
# Project created by QtCreator 2015-03-06T10:52:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileRenamer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filetreeitem.cpp \
    filetreemodel.cpp

HEADERS  += mainwindow.h \
    filetreeitem.h \
    filetreemodel.h

FORMS    += mainwindow.ui
