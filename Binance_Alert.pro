QT       += core gui
QT       += network
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    get_price.cpp \
    main.cpp \
    mainwindow.cpp \
    set_alert.cpp

HEADERS += \
    get_price.h \
    mainwindow.h \
    set_alert.h

FORMS += \
    get_price.ui \
    mainwindow.ui \
    set_alert.ui

TRANSLATIONS += \
    AI_Signal_fa_IR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
