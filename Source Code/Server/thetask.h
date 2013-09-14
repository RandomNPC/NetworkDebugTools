#ifndef THETASK_H
#define THETASK_H

#include <QRunnable>
#include <QObject>
#include <QDebug>

#include <QFile>

class TheTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    TheTask();   

signals:
    void result(QByteArray bit);
    void toClient(QString info);

protected:
    void run();

private:
    QByteArray transfer;
};

#endif // THETASK_H
