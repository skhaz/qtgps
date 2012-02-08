
TEMPLATE = app
TARGET = gps
DESTDIR = output
CONFIG -= console

OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
RCC_DIR = tmp/rcc

QT += webkit network

SOURCES += \
	Main.cpp \
	MainWindow.cpp \
	GpsClient.cpp \

HEADERS += \
	MainWindow.h \
	GpsClient.h \

FORMS += MainWindow.ui \

