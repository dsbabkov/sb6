QT += widgets opengl core
TEMPLATE = app
TARGET = chapter03
INCLUDEPATH += .

HEADERS += \
    movingtri.h \
    tessellatedtri.h \
    tessellatedgstri.h \
    fragcolorfrompos.h
SOURCES += main.cpp \
    movingtri.cpp \
    tessellatedtri.cpp \
    tessellatedgstri.cpp \
    fragcolorfrompos.cpp

OTHER_FILES +=
