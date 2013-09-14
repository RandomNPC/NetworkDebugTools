#include "theclient.h"

TheClient::TheClient(QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(1);
}

void TheClient::setSocket(int descriptor)
{
    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));

    socket->setSocketDescriptor(descriptor);
    fromTask("User " + QString::number(descriptor) +" has connected!");
    clientDesc = descriptor;
}

QTcpSocket *TheClient::getSocket()
{
    return socket;
}

void TheClient::connected(){qDebug() << "connected (fcn)";}

void TheClient::disconnected()
{
    fromTask("User " + QString::number(clientDesc) +" has disconnected!");
    emit clientDC(clientDesc);

}

void TheClient::readyRead()
{
    QByteArray lol = socket->readAll();

    fromTask("Client "+QString::number(clientDesc) + " said: " + lol);


    socket->flush();
}

void TheClient::taskResult(QByteArray res)
{
}

void TheClient::fromTask(QString info)
{
    emit toServer(info);
}
