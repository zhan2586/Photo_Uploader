#-------------------------------------------------
#
# Project created by QtCreator 2019-04-24T17:28:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Photo_Uploader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CMAKE_CXXFLAGS += -std=gnu++14
INCLUDEPATH +="C:\Users\Wenyu\Downloads\Qt\ZipPack\include"
LIBS += -L"C:\Users\Wenyu\Downloads\Qt\ZipPack\lib"
LIBS += -lquazip -lz
