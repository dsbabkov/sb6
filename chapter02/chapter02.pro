QT += widgets opengl core
TEMPLATE = app
TARGET = chapter02
INCLUDEPATH += .

HEADERS += simpleclear.h simpleclear2.h singlepoint.h \
    singletri.h
SOURCES += main.cpp simpleclear.cpp simpleclear2.cpp singlepoint.cpp \
    singletri.cpp
