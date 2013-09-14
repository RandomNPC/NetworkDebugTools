#ifndef THECLIENT_H
#define THECLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>

#include "thetask.h"

class TheClient : public QObject
{
    Q_OBJECT
public:
    explicit TheClient(QObject *parent = 0);
    void setSocket(int descriptor);
    QTcpSocket* getSocket();
    void setDownloadableContent(QString, QByteArray);

signals:
    void toServer(QString info);
    void clientDC(int);

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void taskResult(QByteArray res);
    void fromTask(QString info);

private:
    QTcpSocket *socket;
    int clientDesc;
    QByteArray contentToDownload;
    QString contentName;
};

#endif // THECLIENT_H
