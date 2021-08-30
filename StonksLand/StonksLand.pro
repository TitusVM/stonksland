QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets webchannel

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    country.cc \
    csv.cc \
    currency.cc \
    exchangerate.cpp \
    getinfo.cc \
    infosmonnaie.cpp \
    list.cpp \
    main.cc \
    map.cc \
    maprender.cc \
    stonksland.cc

HEADERS += \
    country.h \
    csv.h \
    currency.h \
    exchangerate.h \
    getinfo.h \
    infosmonnaie.h \
    list.h \
    map.h \
    maprender.h \
    stonksland.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    data.qrc
