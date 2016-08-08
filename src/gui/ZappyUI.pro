#-------------------------------------------------
#
# Project created by QtCreator 2016-06-10T11:58:36
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZappyUI
TEMPLATE = app


SOURCES += main.cpp\
        zappyui.cpp \
    ../client/zappy_communicator.c \
    ../client/zappy_connect_to_server.c \
    ../client/zappy_connect_to_server2.c \
    ../client/zappy_disconnect_from_server.c \
    ../client/zappy_getnextline.c \
    ../client/zappy_recv.c \
    ../client/zappy_return_value_to_string.c \
    ../client/zappy_send.c \
    q2dzappy.cpp \
    ZappyLauncher/launcher.cpp \
    intro.cpp

HEADERS  += zappyui.h \
    ../client/zappy_communicator.h \
    q2dzappy.h \
    zappystructures.h \
    ZappyLauncher/launcher.h \
    intro.h

FORMS    += zappyui.ui \
    ZappyLauncher/widget.ui \
    intro.ui

DEPENDPATH += ./irrlicht/bin/Win32-gcc ./sfml/bin/Win32-gcc
INCLUDEPATH += ../client ./irrlicht/include ./sfml/include/

QMAKE_CFLAGS += -std=gnu11 -Wall -Wextra -W -I../client/

QMAKE_CXXFLAGS += -std=c++11 -I../client/

LIBS += -lws2_32 -L$$PWD/irrlicht/bin/Win32-gcc -lIrrlicht -L$$PWD/sfml/bin/Win32-gcc -lsfml-graphics-2 -lsfml-system-2 -lsfml-window-2
# LIBS += -L$$PWD/sfml/bin/Linux -lsfml-graphics -lsfml-system -lsfml-window

RESOURCES +=

# DISTFILES += \
#     zappyui.rc

RC_FILE = zappyui.rc
