#include "clientpinger.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    clientpinger w;
    w.show();
    
    return a.exec();
}
