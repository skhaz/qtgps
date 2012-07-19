
#include "MainWindow.h"



MainWindow::MainWindow(QWidget *parent)
: QWidget(parent)
{
    setupUi(this);

    update(10,10);

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
    QStringList code;

    code << "if (circle !== null) circle.setMap(null);";
    code << "var circleOptions = {";
    code << "strokeColor: \"#FF0000\",";
    code << "strokeOpacity: 0.8,";
    code << "strokeWeight: 2,";
    code << "fillColor: \"#FF0000\",";
    code << "fillOpacity: 0.35,";
    code << "map: map,";
    code << QString("center: new google.maps.LatLng(%1, %2),").arg(latitude).arg(longitude);
    code << "radius: 20";
    code << "};";
    code << "circle = new google.maps.Circle(circleOptions);";
    qDebug() << code.join("\n");

	view->page()->mainFrame()->evaluateJavaScript(code.join("\n"));
}
