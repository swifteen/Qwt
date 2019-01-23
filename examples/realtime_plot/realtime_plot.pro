TARGET       = realtime
TEMPLATE     = app

CONFIG       = qt
#CONFIG       = qtopia

CONFIG      += thread
CONFIG      += warn_on
#CONFIG      += debug

# Qt 4 compatibility flags
#QT               += compat
#DEFINES          += QT_COMPAT

qtopia:CONFIG  -= thread
qtopia:DEFINES += QWT_QTOPIA

MOC_DIR      = moc
OBJECTS_DIR  = obj
INCLUDEPATH += ../../include
DEPENDPATH  += ../../include

unix:LIBS += -L../../lib -lqwt

win32:DEFINES  += QT_DLL QWT_DLL
win32:LIBS     += ../../lib/qwt.lib

linux-g++:TMAKE_CXXFLAGS += -fno-exceptions 

HEADERS = \
	mainwindow.h \
	scrollzoomer.h \
	scrollbar.h \
	incrementalplot.h \
	randomplot.h

SOURCES = \
	realtime.cpp \
	mainwindow.cpp \
	scrollzoomer.cpp \
	scrollbar.cpp \
	incrementalplot.cpp \
	randomplot.cpp

