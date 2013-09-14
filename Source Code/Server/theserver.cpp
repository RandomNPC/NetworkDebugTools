#include "theserver.h"

TheServer::TheServer(QObject *parent) :
    QTcpServer(parent)
{
}

void TheServer::startServer(QString text)
{
    if(this->listen(QHostAddress::Any,text.toUShort())){
        fromClient("Server started using Port: " + text);
        emit serverStarted(this->serverAddress().toString());
        clientSocket.clear();
        emit clientUpdate(clientSocket);
    }
    else{
        fromClient("Server failed to start on Port: " + text);
        emit serverStopped();
    }
}

void TheServer::stopServer()
{
    this->close();
    //iterator to kill all connections!!!
    foreach(int i,clientSocket.keys()){
        QTcpSocket *kill = clientSocket.value(i);
        kill->close();
        clientSocket.remove(i);
        clientlist.remove(i);
    }
    fromClient("Server stopped");
    emit serverStopped();
    emit clientUpdate(clientSocket);
}

void TheServer::incomingConnection(int descriptor)
{
    TheClient *client = new TheClient(this);
    connect(client,SIGNAL(toServer(QString)),this,SLOT(fromClient(QString)));
    connect(client,SIGNAL(clientDC(int)),this,SLOT(clienthasDC(int)));
    client->setSocket(descriptor);
    clientSocket.insert(descriptor,client->getSocket());
    clientlist.insert(descriptor,client);
    emit clientUpdate(clientSocket);
}

void TheServer::fromClient(QString info)
{
    emit toGui(info);
}

void TheServer::clienthasDC(int key)
{
   clientSocket.remove(key);
   clientlist.remove(key);
   emit clientUpdate(clientSocket);
}
