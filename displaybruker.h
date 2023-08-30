#ifndef DISPLAYBRUKER_H
#define DISPLAYBRUKER_H

#include "io.h"

QString _scriptDirectory    = "/space/deltabp/1/users/public/script/Bruker/";

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
CommandOptions _inputOptions;


class displayBruker
{
private:
    CommandOptions _inputOptions;

    CommandLineParseResult parseCommandLine(QStringList commandLine);

public:
    displayBruker();
    void readCommandLine();
    int determineDirectoryType();
    void displayFM(int type);
};

#endif // DISPLAYBRUKER_H
