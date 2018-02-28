#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T15:21:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = enmessage
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    encrypt_str.cpp \
    main_ui.cpp \
    hash_str.cpp \
    std_rand.cpp

HEADERS += \
    encrypt_str.h \
    main_ui.h \
    hash_str.h \
    std_rand.h

FORMS += \
    main_ui.ui

LIBS += -lcryptopp

TRANSLATIONS += enmessage.ts

#DISTFILES += \
#    enmessage.ts

CONFIG += c++11
