TARGET       = bode
TEMPLATE     = app

CONFIG       = qt 
#CONFIG       = qtopia

CONFIG      += thread
CONFIG      += warn_on 
#CONFIG      += debug 

qtopia:CONFIG  -= thread
qtopia:DEFINES += QWT_QTOPIA

# Qt 4 compatibility flags
#QT               += compat
#DEFINES          += QT_COMPAT 

MOC_DIR      = moc
OBJECTS_DIR  = obj
INCLUDEPATH += ../../include
DEPENDPATH  += ../../include

unix:LIBS += -L../../lib -lqwt

win32:DEFINES  += QT_DLL QWT_DLL
win32:LIBS     += ../../lib/qwt.lib

linux-g++:TMAKE_CXXFLAGS += -fno-exceptions 

HEADERS = bode.h bode_plot.h cplx.h pixmaps.h
SOURCES = bode.cpp bode_plot.cpp
