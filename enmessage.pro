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
    std_rand.cpp \
    cryptopp_ecdh_algorithm.cpp \
    gui_key_exchange_wizard.cpp \
    gui_main.cpp \
    os_clipboard.cpp \
    cryptopp_aes_algorithm.cpp \
    cryptopp_hash_algorithm.cpp \
    qt_keyfile.cpp \
    cryptopp_encoder.cpp \
    qt_gen_filedialog.cpp

HEADERS += \
    std_rand.h \
    cryptopp_ecdh_algorithm.h \
    gui_key_exchange_wizard.h \
    gui_main.h \
    os_clipboard.h \
    cryptopp_aes_algorithm.h \
    cryptopp_hash_algorithm.h \
    qt_keyfile.h \
    cryptopp_encoder.h \
    qt_gen_filedialog.h

FORMS += \
    gui_main.ui \
    gui_key_exchange_wizard.ui

LIBS += -lcryptopp

TRANSLATIONS += enmessage.ts

#DISTFILES += \
#    enmessage.ts

CONFIG += c++17

RESOURCES += \
    gui_resource.qrc
