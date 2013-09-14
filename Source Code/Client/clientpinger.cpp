#include "clientpinger.h"
#include "ui_clientpinger.h"

clientpinger::clientpinger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientpinger)
{
    ui->setupUi(this);

    this->setWindowTitle("Client Pinger");

    ui->disconnectme->setEnabled(false);
    ui->textIn->setEnabled(false);
    ui->sendText->setEnabled(false);

        QList<QHostAddress> targets;

        foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
                 targets.push_back(address);
        }

        if(targets.size()==2){
            ui->IPinternal->setText(targets[0].toString());
            ui->IPexternal->setText(targets[1].toString());
        }
}
clientpinger::~clientpinger()
{
    delete ui;
}

void clientpinger::readyRead()
{
    QByteArray stuff = plug->readAll();
    if(stuff.size()>0) ui->connectinfo->addItem("Data recieved! " + stuff);
    plug->flush();
}

void clientpinger::on_connectme_clicked()
{
    plug = new QAbstractSocket(QAbstractSocket::TcpSocket,this);
    ui->connectme->setEnabled(false);
    ui->disconnectme->setEnabled(true);
    ui->IPport->setEnabled(false);
    ui->IPtext->setEnabled(false);
    plug->connectToHost(ui->IPtext->text(),ui->IPport->text().toUShort());

    connect(plug,SIGNAL(readyRead()),this,SLOT(readyRead()));

    if(plug->waitForConnected(3000)){
        ui->connectinfo->addItem("Successful connection to " + ui->IPtext->text() + " Port " + ui->IPport->text());
        ui->textIn->setEnabled(true);
        ui->sendText->setEnabled(true);
    }
    else{
        ui->connectinfo->addItem("Could not connect to "+ ui->IPtext->text() + " Port " + ui->IPport->text());
        on_disconnectme_clicked();
    }
}

void clientpinger::on_disconnectme_clicked()
{
    plug->close();
    ui->textIn->setEnabled(false);
    ui->sendText->setEnabled(false);
    ui->connectme->setEnabled(true);
    ui->disconnectme->setEnabled(false);
    ui->IPport->setEnabled(true);
    ui->IPtext->setEnabled(true);
}


void clientpinger::on_sendText_clicked()
{
    plug->write(ui->textIn->text().toLocal8Bit());
    ui->connectinfo->addItem("Sent text: " + ui->textIn->text() + " to: " + ui->IPtext->text() + " Port " + ui->IPport->text());
}

