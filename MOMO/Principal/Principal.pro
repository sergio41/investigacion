#-------------------------------------------------
#
# Project created by QtCreator 2014-01-30T13:06:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Principal
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    simbolos.cpp \
    parser.cpp \
    almacenador.cpp \
    binarytreenode.cpp \
    binarytree.cpp \
    almacen.cpp \
    ventana.cpp \
    logicaVentana.cpp

HEADERS  += mainwindow.h \
    simbolos.h \
    parser.h \
    almacenador.h \
    binarytreenode.h \
    binarytree.h \
    almacen.h \
    ventana.h

FORMS    += mainwindow.ui \
    ventana.ui
