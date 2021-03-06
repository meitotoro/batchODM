#-------------------------------------------------
#
# Project created by QtCreator 2018-06-29T10:55:15
#
#-------------------------------------------------

QT       += core gui
QT += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = batchODM
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
    taskdialog.cpp \
    imagelistitem.cpp \
    taskmanager.cpp \
    task.cpp \
    task.cpp \
    sendfiles.cpp \
    docker.cpp \
    build/debug/moc_docker.cpp \
    build/debug/moc_imagelistitem.cpp \
    build/debug/moc_mainwindow.cpp \
    build/debug/moc_sendfiles.cpp \
    build/debug/moc_task.cpp \
    build/debug/moc_taskdialog.cpp \
    build/debug/moc_taskmanager.cpp \
    docker.cpp \
    imagelistitem.cpp \
    main.cpp \
    mainwindow.cpp \
    sendfiles.cpp \
    task.cpp \
    taskdialog.cpp \
    taskmanager.cpp

HEADERS += \
        mainwindow.h \
    taskdialog.h \
    imagelistitem.h \
    taskmanager.h \
    task.h \
    sendfiles.h \
    docker.h \
    build/debug/moc_predefs.h \
    build/ui_imagelistitem.h \
    build/ui_mainwindow.h \
    build/ui_taskdialog.h \
    docker.h \
    imagelistitem.h \
    mainwindow.h \
    sendfiles.h \
    task.h \
    taskdialog.h \
    taskmanager.h

FORMS += \
        mainwindow.ui \
    taskdialog.ui \
    imagelistitem.ui

DISTFILES += \
    images/icons8-add-new-50.png \
    images/icons8-add-new-50.png

RESOURCES += \
    images.qrc
