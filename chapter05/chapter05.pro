QT += widgets opengl core
TEMPLATE = app
TARGET = chapter05
INCLUDEPATH += .

HEADERS += spinnycube.h \
    simpletexture.h
SOURCES += main.cpp \
    spinnycube.cpp \
    simpletexture.cpp


OTHER_FILES +=

RESOURCES += \
    chapter05.qrc
