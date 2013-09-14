#ifndef CLIENTPINGER_H
#define CLIENTPINGER_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>

#include <QFile>

namespace Ui {
class clientpinger;
}

class clientpinger : public QDialog
{
    Q_OBJECT
    
public:
    explicit clientpinger(QWidget *parent = 0);
    ~clientpinger();

public slots:
    void readyRead();

private slots:

    void on_connectme_clicked();

    void on_disconnectme_clicked();

    void on_sendText_clicked();

protected:

private:
    Ui::clientpinger *ui;
    QAbstractSocket *plug;
};

#endif // CLIENTPINGER_H
