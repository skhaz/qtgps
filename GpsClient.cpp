
#include <GpsClient.h>



GpsClient::GpsClient(QObject *parent)
: QThread(parent)
{

}

void GpsClient::run()
{
	const int timeout = 1000;

	QTcpSocket socket;

	socket.connectToHost(QHostAddress::LocalHost, 2947);

	if (!socket.waitForConnected(timeout))
	{
		qDebug() << "Failed to connect!";
		return;
	}

	socket.write("?WATCH={\"enable\":true,\"json\":false, \"nmea\":true}");

	forever
	{
		socket.waitForReadyRead();

		QString data = socket.readAll();

		QStringList result = data.split('$');

		for (int i = 0; i <result.length(); ++i)
		{
			QString subset = result[i].left(5);

			if (subset.compare("GPRMC") == 0)
			{
				parse(result[i]);
			}
		}
	}
}

void GpsClient::parse(QString const& rmc)
{
	// TODO: Add checksum check
	double longitude = 0, latitude = 0;

	QStringList array = rmc.split(',');

	if (array.length() > 9)
	{

		if (array[2].compare("A") != 0)
		{
			qDebug() << "invalid data!";
			return;
		}


		if (array[3].length() >= 3)
		{
			latitude = array[3].left(2).toDouble() + (array[3].mid(2).toDouble() / 60.0);

			if (array[4].compare("S") == 0)
				latitude *= -1.0;
		}

		if (array[5].length() >= 4)
		{
			longitude = array[5].left(3).toDouble() + (array[5].mid(3).toDouble() / 60.0);

			if (array[6].compare("W") == 0)
				longitude *= -1.0;
        }

		emit position(latitude, longitude);
	}
}


