QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chopeo.cpp \
    com_chose.cpp \
    game_base.cpp \
    game_computer.cpp \
    herores.cpp \
    ko.cpp \
    ma.cpp \
    main.cpp \
    game_main.cpp \
    people.cpp \
    sign.cpp \
    signin.cpp \
    start.cpp \
    udp_chose.cpp \
    udp_game.cpp

HEADERS += \
    GAME_define.h \
    chopeo.h \
    com_chose.h \
    game_base.h \
    game_computer.h \
    game_main.h \
    herores.h \
    ko.h \
    ma.h \
    people.h \
    sign.h \
    signin.h \
    start.h \
    udp_chose.h \
    udp_game.h

FORMS += \
    chopeo.ui \
    com_chose.ui \
    game_computer.ui \
    game_main.ui \
    ko.ui \
    ma.ui \
    sign.ui \
    signin.ui \
    start.ui \
    udp_chose.ui \
    udp_game.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
