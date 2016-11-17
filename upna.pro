qnx {
 target.path = /tmp/$${TARGET}/bin
 INSTALLS += target
}

INCLUDEPATH = /opt/qnx650/target/qnx6/opt/qt486/include/QtSerialPort

TEMPLATE = app
TARGET = upna
CONFIG += serialport
QT += core \
    gui \
    network
HEADERS += \
    helpers.h \
    kama.pb.h \
    frame.h \
    framehandler.h \
    mainwindow.h \
    convertation.h \
    pointingsuploader.h \
    controlserver.h \
    settingsdialog.h \
    crc.h
SOURCES += \
    kama.pb.cc \
    framehandler.cpp \
    main.cpp \
    mainwindow.cpp \
    convertation.cpp \
    pointingsuploader.cpp \
    controlserver.cpp \
    settingsdialog.cpp
LIBS += -lprotobuf -lQtSerialPort
FORMS += settingsdialog.ui \
    mainwindow.ui
RESOURCES += resourses.qrc

OTHER_FILES += \
    kama.proto
