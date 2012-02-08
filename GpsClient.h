
#ifndef _GpsClient_h
#define _GpsClient_h

#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QStringList>
#include <QString>



class GpsClient : public QThread
{
    public:
        GpsClient(QObject *parent = 0);

        void run();

    signals:
        void position(double, double);

    protected:
        void parse(QString const& rmc);

    private:
        Q_OBJECT
};

#endif

