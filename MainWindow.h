
#ifndef _MainWindow_h
#define _MainWindow_h

#include <QApplication>
#include <QWidget>
#include <QMainWindow>

#include "ui_MainWindow.h"



class MainWindow : public QMainWindow, private Ui_MainWindow
{
	public:
		MainWindow(QWidget *parent = 0);

		~MainWindow();

	private:
		Q_OBJECT
};

#endif

