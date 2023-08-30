#include <QCoreApplication>
#include <QDebug>
#include "displaybruker.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    displayBruker bruker;

    bruker.readCommandLine();
    FUNC_INFO << "_inputOptions.directoryName" << _inputOptions.directoryName;
    int type = bruker.determineDirectoryType();
    FUNC_INFO << "type" << type;
    bruker.displayFM(type);
//    a.exec();
}

