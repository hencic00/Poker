######################################################################
# Automatically generated by qmake (3.0) Mon Oct 23 11:34:53 2017
######################################################################

TEMPLATE = app
TARGET = Projekt
INCLUDEPATH += .

# Input
HEADERS += ./headers/pokerWindow.h ./headers/loginPage.h ./headers/signUpPage.h ./headers/loadingPage.h
HEADERS += ./headers/lobbyPage.h ./headers/playPage.h ./headers/renderWidget.h ./headers/connectionHandler/connectionHandler.h

SOURCES += main.cpp ./sources/pokerWindow.cpp ./sources/loginPage.cpp ./sources/signUpPage.cpp ./sources/loadingPage.cpp
SOURCES += ./sources/lobbyPage.cpp ./sources/playPage.cpp ./sources/renderWidget.cpp ./sources/connectionHandler/connectionHandler.cpp

QT += widgets 
QT += svg

CONFIG += warn_off

INCLUDEPATH += ./headers
OBJECTS_DIR = ./mocTrash/objectFiles
MOC_DIR = ./mocTrash/sources