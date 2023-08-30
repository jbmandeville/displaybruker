#include <QCoreApplication>
#include <QCommandLineParser>
#include <QRegularExpression>
#include "displaybruker.h"

void readCommandLine();
CommandLineParseResult parseCommandLine(QStringList commandLine);

displayBruker::displayBruker()
{
}

void displayBruker::readCommandLine()
{
    QStringList commandLine = QCoreApplication::arguments();

    switch (parseCommandLine(commandLine))
    {
    case CommandLineOk:
        break;
    case CommandLineError:
        exit(1);
    case CommandLineHelpRequested:
        QCoreApplication::exit(0);
    }
}

CommandLineParseResult displayBruker::parseCommandLine(QStringList commandLine)
{
    FUNC_ENTER << commandLine;
    QCommandLineParser parser;
    QString HelpText = "\nCalculate Ki values for several ROIs using table files.\n";
    HelpText.append("Syntax:  exe [Variable-TR table] [short-TE table] [long TE-table] [optional args]\n\n");
    HelpText.append("where\n\n");
    HelpText.append("tables have 1 header line (x lesion contra sinus) followed by time points");
    parser.setApplicationDescription(HelpText);

    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    parser.addPositionalArgument("[directory name]", "A Bruker directory.");

    const QCommandLineOption helpOption = parser.addHelpOption();

    bool success = parser.parse(commandLine);
    if ( !success || parser.isSet(helpOption))
        QTextStream(stdout) << parser.helpText();
    if ( !success ) return CommandLineError;

    int numberArguments = commandLine.count();
    if ( numberArguments < 2 )   // executable [directory name]
        return CommandLineError;
    _inputOptions.startupText = parser.helpText();

    // positional arguments: [directory name]
    if ( parser.positionalArguments().size() < 1 ) return CommandLineError;
    _inputOptions.directoryName  = parser.positionalArguments().at(0);

    return CommandLineOk;
}

int displayBruker::determineDirectoryType()
{
    QString fileName = _inputOptions.directoryName + "/pdata/1/visu_pars";

    QFileInfo checkFile(fileName);
    if ( !(checkFile.exists() && checkFile.isFile()) )
        return -1;

    QFile infile(fileName);
    if (!infile.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;
    QTextStream in_stream(&infile);

    while (!in_stream.atEnd())
    {
        QString line = in_stream.readLine();
        if ( line.isEmpty() ) continue;
        FUNC_INFO << "line" << line;
        QRegularExpression filter("[=,\\s]");// match a comma or a space
        QStringList stringList = line.split(filter);  // clazy:exclude=use-static-qregularexpression
        QString parameter = stringList.at(0);
        FUNC_INFO << stringList << stringList;
        FUNC_INFO << "parameter" << parameter;
        if ( !parameter.compare("##$VisuFGOrderDesc",Qt::CaseInsensitive) )
        {
            line = in_stream.readLine();
            QRegularExpression filter("[()<>,\\s]");// match a comma or a space
            QStringList stringList = line.split(filter);  // clazy:exclude=use-static-qregularexpression
            if ( stringList.contains("FG_ECHO") )
                return 1;
            else
                return 0;
        }
    }
    infile.close();
    FUNC_EXIT;
    return 0;
}

void displayBruker::displayFM(int type)
{
    QString exe;
    if ( type == 1 )
        exe = _scriptDirectory + "reorder.script";
    else
        exe = _scriptDirectory + "view.script";

    QString fileName = _inputOptions.directoryName + "/pdata/1/visu_pars";
    QStringList arguments;
    arguments.append(fileName);

    auto *process = new QProcess();
    process->start(exe,arguments);
}
