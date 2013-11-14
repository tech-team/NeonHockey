TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    spriteinfo.cpp \
    resourcemanager.cpp \
    puck.cpp \
    player.cpp \
    paddle.cpp \
    gfxobject.cpp \
    game.cpp \
    client.cpp

HEADERS += \
    spriteinfo.h \
    resourcemanager.h \
    puck.h \
    player.h \
    paddle.h \
    main.h \
    gfxobject.h \
    game.h \
    client.h


QMAKE_CXXFLAGS += -std=c++11

unix {
    DEFINES += PLATFORM_UNIX

    INCLUDEPATH += /usr/local/include/hge-unix/include \
		   /usr/include/SDL
    LIBS += /usr/local/include/hge-unix/src/core/libhge.so \
	    /usr/local/include/hge-unix/src/core/libhge_helpers.so \
	    -L/usr/local/lib \
	    -lboost_system
}

win32 {
    DEFINES += _WINDOWS
    DEFINES += WIN32_LEAN_AND_MEAN

    INCLUDEPATH += C:/Projects/Qt/hge-unix/include/
    LIBS += C:/Projects/Qt/hge-unix/libs/src/core/libhge.dll.a

    INCLUDEPATH += C:/Projects/Qt/boost_1_54_0
    LIBS += -LC:/Projects/Qt/boost_1_54_0/stage/lib/ \
	-lws2_32
    LIBS += C:/Projects/Qt/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-sd-1_54.a
}
