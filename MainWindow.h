
#ifndef _MainWindow_h
#define _MainWindow_h

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QFile>
#include <QWebFrame>
#include <QList>
#include <QPair>
#include <QtDebug>

#include "GpsClient.h"

#include "ui_MainWindow.h"



class MainWindow : public QWidget, private Ui_MainWindow
{
    public:
        MainWindow(QWidget *parent = 0);

        ~MainWindow();

    protected slots:
        void update(double latitude, double longitude);

    private:
        Q_OBJECT

        GpsClient *gps;
};

#endif

