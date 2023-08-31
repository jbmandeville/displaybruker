#include <QCoreApplication>
#include <QDebug>
#include "displaybruker.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    displayBruker bruker;

    bruker.readCommandLine();
    int type = bruker.determineDirectoryType();
    FUNC_INFO << "type" << type;
    bruker.displayFM(type);
    a.exec();
    exit(0);
}

