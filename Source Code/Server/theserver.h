#ifndef THESERVER_H
#define THESERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>

#include "theclient.h"

class TheServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TheServer(QObject *parent = 0);
    void startServer(QString text);
    void stopServer();
    void setDownloadableContent(QString,QByteArray);
private:
    QHash<int,QTcpSocket*> clientSocket;
    QHash<int,TheClient*> clientlist;

protected:
    void incomingConnection(int descriptor);

signals:
    void toGui(QString info);
    void serverStarted(QString);
    void serverStopped();
    void clientUpdate(QHash<int,QTcpSocket*>);

public slots:
    void fromClient(QString info);
    void clienthasDC(int);
};

#endif // THESERVER_H
