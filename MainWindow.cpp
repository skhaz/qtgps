
#include "MainWindow.h"



MainWindow::MainWindow(QWidget *parent)
: QWidget(parent)
{
	setupUi(this);

    gps = new GpsClient(this);

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
    QPair<double, double> temp = qMakePair(latitude, longitude);

    if (coordinates.isEmpty()) {
        coordinates << temp;
    } else {
        if (coordinates.last() != temp) {
            coordinates << temp;
            qDebug() << coordinates.last() << temp;
        }

        else {
            return;
        }
    }

    QStringList array, code;

    for (int i = 0; i < coordinates.size(); ++i) {
        QPair<double, double> coordinate = coordinates[i];
        array << QString("new GLatLng(%1, %2)").arg(latitude).arg(longitude);
    }

    code << "map.clearOverlays()";
    code << QString("var pos = new GLatLng(%1, %2);").arg(latitude).arg(longitude);
    code << "map.setCenter(pos, 19);";
    code << "var marker = new GMarker(pos);";
    code << "map.addOverlay(marker);";

    code << QString("var polyline = new GPolyline([%1],\"#0000dd\", 6, 0.4);").arg(array.join(","));
    code << "map.addOverlay(polyline);";

	view->page()->mainFrame()->evaluateJavaScript(code.join("\n"));
}
