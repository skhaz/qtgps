
#include "MainWindow.h"



MainWindow::MainWindow(QWidget *parent)
: QWidget(parent)
, gps(new GpsClient(this))
{
	setupUi(this);

	// gps->start();

	connect(gps, SIGNAL(position(double, double)), SLOT(update(double, double)));
	connect(view, SIGNAL(loadProgress(int)), progressBar, SLOT(setValue(int)));
	connect(view, SIGNAL(loadStarted()), progressBar, SLOT(show()));
	connect(view, SIGNAL(loadFinished(bool)), progressBar, SLOT(hide()));
	connect(view, SIGNAL(loadFinished(bool)), gps, SLOT(start()));

	QFile file("index.html");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
		QString html = QTextStream(&file).readAll();
		view->setHtml(html);
	}
}

MainWindow::~MainWindow()
{
}

void MainWindow::update(double latitude, double longitude)
{
	QStringList code;
	code << QString("var pos = new GLatLng(%1, %2);").arg(latitude).arg(longitude);
	code << "map.setCenter(pos, 17);";
	code << "var marker = new GMarker(pos);";
	code << "map.addOverlay(marker);";

	view->page()->mainFrame()->evaluateJavaScript(code.join("\n"));
}



