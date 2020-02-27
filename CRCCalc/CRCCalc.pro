#-------------------------------------------------
#
# Project created by QtCreator 2020-01-04T17:14:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = CRCCalc
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
        src/main.cpp \
        src/crccalc.cpp \
        src/crc.c


HEADERS += \
        inc/crccalc.h \
        inc/crc.h \
    inc/constString.h

RC_ICON = res/general/OCR-cyan.ico

FORMS     += ui/crccalc.ui
#RESOURCES += res/images.qrc

# 头文件包含路径
INCLUDEPATH += inc
# ui.h输出路径
UI_DIR += ./ui
# 可执行文件.exe输出路径
DESTDIR = ./exe

