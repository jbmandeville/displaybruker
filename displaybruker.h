#ifndef DISPLAYBRUKER_H
#define DISPLAYBRUKER_H

#include "io.h"
#include <QObject>

enum CommandLineParseResult
{
    CommandLineOk,
    CommandLineError,
    CommandLineHelpRequested
};
struct CommandOptions
{
    QString directoryName;   // positional argument 1
    QString startupText;         // help
};


class displayBruker : public QObject
{
    Q_OBJECT
private:
    QString _scriptDirectory    = "/space/deltabp/1/users/public/script/Bruker/";
    CommandOptions _inputOptions;

    CommandLineParseResult parseCommandLine(QStringList commandLine);    

public:
    displayBruker();
    void readCommandLine();
    int determineDirectoryType();
    void displayFM(int type);
public slots:
    void exitApp(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif // DISPLAYBRUKER_H
