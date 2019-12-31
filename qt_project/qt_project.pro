#-------------------------------------------------
#
# Project created by QtCreator 2019-12-14T17:34:40
#
#-------------------------------------------------

QT       += widgets core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_project
TEMPLATE = app
LIBS += -L/usr/local/lib -lGLU
# LIBS +=-lopengl32 -lglu32

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
    drawingarea.cpp \
    door.cpp \
    window.cpp \
    wall.cpp \
    inputdialog.cpp \
    floor.cpp \
    wallsmodelview.cpp

HEADERS += \
        mainwindow.h \
    drawingarea.h \
    door.h \
    window.h \
    wall.h \
    inputdialog.h \
    floor.h \
    wallsmodelview.h

FORMS += \
    inputdialog.ui
