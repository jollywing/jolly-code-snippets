
TEMPLATE = app
CONFIG += qt
TARGET = main
INCLUDEPATH += $$PWD/../widgets
win32:CONFIG(debug, debug|release):LIBS += -L$$OUT_PWD/../widgets/debug/ -lwidgets

SOURCES += main.cpp
