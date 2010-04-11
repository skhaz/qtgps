
TEMPLATE = app
TARGET = gps
DESTDIR = output
CONFIG += console

OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
RCC_DIR = tmp/rcc

QT += webkit

SOURCES += \
	Main.cpp \
	MainWindow.cpp \

HEADERS += \
	MainWindow.h \

FORMS += MainWindow.ui \

