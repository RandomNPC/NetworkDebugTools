#ifndef SERVERMAIN_H
#define SERVERMAIN_H

#include <QDialog>
#include <QDebug>
#include <QFileDialog>
#include <QFile>

#include "theserver.h"

namespace Ui {
class serverMain;
}

class serverMain : public QDialog
{
    Q_OBJECT
    
public:
    explicit serverMain(QWidget *parent = 0);
    ~serverMain();

private slots:
    void on_sendText_clicked();

    void on_stopServer_clicked();

    void on_startServer_clicked();

public slots:
    void addToLog(QString info);
    void onServerStarted(QString address);
    void onServerStopped();
    void clientList(QHash<int,QTcpSocket*>);
    void sendToClients(QString);

signals:


private:
    Ui::serverMain *ui;
    TheServer server;
    QHash<int,QTcpSocket*> clients;
};

#endif // SERVERMAIN_H
