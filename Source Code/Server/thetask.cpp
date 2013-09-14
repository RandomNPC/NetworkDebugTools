#include "thetask.h"

TheTask::TheTask()
{
}

QString encodeCArray(QByteArray data){
    return data.toHex();
}


void TheTask::run()
{
    emit result("");

}
