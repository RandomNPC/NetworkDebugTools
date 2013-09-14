#include "servermain.h"
#include "ui_servermain.h"

serverMain::serverMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serverMain)
{
    ui->setupUi(this);
    connect(&server,SIGNAL(toGui(QString)),this,SLOT(addToLog(QString)));
    connect(&server,SIGNAL(toGui(QString)),this,SLOT(sendToClients(QString)));
    connect(&server,SIGNAL(serverStarted(QString)),this,SLOT(onServerStarted(QString)));
    connect(&server,SIGNAL(serverStopped()),this,SLOT(onServerStopped()));
    connect(&server,SIGNAL(clientUpdate(QHash<int,QTcpSocket*>)),this,SLOT(clientList(QHash<int,QTcpSocket*>)));
    ui->stopServer->setEnabled(false);

    ui->serverIP->setEnabled(false); //this function may not be used
    ui->textTosend->setEnabled(false);
    ui->sendText->setEnabled(false);
}

serverMain::~serverMain()
{
    delete ui;
}

void serverMain::sendToClients(QString message)
{
    foreach(int i, clients.keys()){
        QTcpSocket *send = clients.value(i);
        send->write(message.toLocal8Bit());
    }
}

void serverMain::addToLog(QString info)
{
    ui->serverInfo->addItem(info);
}


void serverMain::onServerStarted(QString address)
{
    ui->serverPort->setEnabled(false);
    ui->startServer->setEnabled(false);
    ui->stopServer->setEnabled(true);
    ui->serverIP->setText(address);
    ui->textTosend->setEnabled(true);
    ui->sendText->setEnabled(true);
}

void serverMain::onServerStopped()
{
    ui->serverPort->setEnabled(true);
    ui->startServer->setEnabled(true);
    ui->stopServer->setEnabled(false);
    ui->textTosend->setEnabled(false);
    ui->sendText->setEnabled(false);
}

void serverMain::clientList(QHash<int, QTcpSocket *> list)
{
    clients = list;
}

void serverMain::on_sendText_clicked()
{
    addToLog("Server said: " + ui->textTosend->text().toLocal8Bit());
    sendToClients("Server said: " + ui->textTosend->text());
}

void serverMain::on_stopServer_clicked()
{
    server.stopServer();
}

void serverMain::on_startServer_clicked()
{
    server.startServer(ui->serverPort->text()); //start on the port!
}
