#-------------------------------------------------
#
# Project created by QtCreator 2017-10-25T19:21:58
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = manage_system
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    add_dialog.cpp \
    edit_dialog.cpp \
    password_dialog.cpp

HEADERS  += mainwindow.h \
    add_dialog.h \
    edit_dialog.h \
    password_dialog.h

FORMS    += mainwindow.ui \
    add_dialog.ui \
    edit_dialog.ui \
    password_dialog.ui
qtHaveModule(printsupport): QT += printsupport

RESOURCES += \
    icon.qrc

