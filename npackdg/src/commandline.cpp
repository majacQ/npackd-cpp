#include <windows.h>

#include <QCoreApplication>

#include "commandline.h"

bool CommandLine::Option::nameMatches(const QString& name)
{
    bool r;
    if (name.length() == 1 && name.at(0) == name2) {
        r = true;
    } else if (this->name == name) {
        r = true;
    } else {
        r = false;
    }

    return r;
}

CommandLine::CommandLine()
{
}

CommandLine::~CommandLine()
{
    qDeleteAll(this->options);
    qDeleteAll(this->parsedOptions);
}

QString CommandLine::processOneParam(QStringList* params)
{
    QString err;

    QString p = params->at(0);
    bool nameFound = false;
    bool valueFound = false;
    QString name;
    QString value;

    if (p == "--" || p == "-") {
        err = QString(QObject::tr("Missing option name: %1")).arg(p);
    } else if (p.startsWith("--")) {
        int pos = p.indexOf("=");
        if (pos == 2) {
            err = QString(QObject::tr("Option name expected: %1")).arg(p);
        } else if (pos >= 0) {
            name = p.mid(2, pos - 2);
            value = p.right(p.length() - pos - 1);
            nameFound = true;
            valueFound = true;
            params->removeAt(0);
        } else {
            name = p.right(p.length() - 2);
            nameFound = true;
            params->removeAt(0);
        }
    } else if (p.startsWith("-")) {
        int pos = p.indexOf("=");
        if (pos == 1) {
            err = QString(QObject::tr("Option name cannot start with the equality sign: %1")).
                    arg(p);
        } else if (pos > 2) {
            err = QString(QObject::tr("Only one-letter options can start with a minus sign: %1")).
                    arg(p);
        } else if (pos == 2) {
            name = p.mid(1, 1);
            value = p.right(p.length() - 3);
            nameFound = true;
            valueFound = true;
            params->removeAt(0);
        } else {
            if (p.length() > 2) {
                err = QString(QObject::tr("Only one-letter options can start with a minus sign: %1")).
                        arg(p);
            } else {
                name = p.mid(1, 1);
                nameFound = true;
                params->removeAt(0);
            }
        }
    }

    // WPMUtils::outputTextConsole << name) << " --> " << value) <<
    //        " : " << err) << nameFound << valueFound << std::endl;

    if (err.isEmpty()) {
        if (nameFound) {
            // WPMUtils::outputTextConsole << "Searching: " << name) << std::endl;
            Option* opt = findOption(name);
            if (!opt) {
                err = QString(QObject::tr("Unknown option: %1")).arg(name);
            } else {
                if (opt->valueDescription.isEmpty() && valueFound) {
                    err = QString(QObject::tr("Unexpected value for the option %1")).arg(name);
                } else {
                    ParsedOption* po = new ParsedOption();
                    po->opt = opt;
                    this->parsedOptions.append(po);
                    if (valueFound)
                        po->value = value;
                    else {
                        if (!opt->valueDescription.isEmpty()) {
                            if (params->count() == 0) {
                                err = QString(QObject::tr("Missing value for the option %1")).
                                        arg(name);
                            } else {
                                po->value = params->at(0);
                                params->removeAt(0);
                            }
                        }
                    }
                }
            }
        } else {
            ParsedOption* po = new ParsedOption();
            po->opt = nullptr;
            this->parsedOptions.append(po);
            po->value = params->at(0);
            params->removeAt(0);
        }
    }

    return err;
}

CommandLine::Option* CommandLine::findOption(const QString& name)
{
    Option* r = nullptr;
    for (int i = 0; i < this->options.count(); i++) {
        Option* opt = this->options.at(i);
        if (opt->nameMatches(name)) {
            r = opt;
            break;
        }
    }
    return r;
}

void CommandLine::add(QString name, char name2, QString description,
        QString valueDescription, bool multiple, const QString &allowedCommands)
{
    Option* opt = new Option();
    opt->name = name;
    opt->name2 = name2;
    opt->description = description;
    opt->valueDescription = valueDescription;
    opt->multiple = multiple;
    opt->allowedCommands = allowedCommands.split(',');
    if (opt->allowedCommands.count() == 1 &&
            opt->allowedCommands.at(0).isEmpty()) {
        opt->allowedCommands.clear();
    }

    this->options.append(opt);
}

QStringList CommandLine::printOptions() const
{
    QStringList names;
    int len = 0;
    for (int i = 0; i < this->options.count(); i++) {
        Option* opt = this->options.at(i);
        QString s("    ");
        if (opt->name2 != 0) {
            s.append("-").append(opt->name2).append(", ");
        } else {
            s.append("    ");
        }
        if (!opt->name.isEmpty()) {
            s.append("--").append(opt->name);
        }
        names.append(s);
        if (s.length() > len)
            len = s.length();
    }

    QStringList result;

    result.append("Global options:");
    for (int i = 0; i < this->options.count(); i++) {
        Option* opt = this->options.at(i);
        if (opt->allowedCommands.isEmpty()) {
            QString s = names.at(i);
            s += QString().fill(' ', len + 4 - s.length());
            s.append(opt->description);
            result.append(s);
        }
    }

    result.append("Options:");
    for (int i = 0; i < this->options.count(); i++) {
        Option* opt = this->options.at(i);
        if (!opt->allowedCommands.isEmpty()) {
            QString s = names.at(i);
            s += QString().fill(' ', len + 4 - s.length());
            s.append(opt->description);
            result.append(s);
        }
    }

    return result;
}

QString CommandLine::parse()
{
    QString err;
    QStringList params;

    int nArgs;
    LPWSTR* szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    if (nullptr == szArglist) {
        err = QObject::tr("CommandLineToArgvW failed");
    } else {
        for(int i = 1; i < nArgs; i++) {
            QString s = QString::fromWCharArray(szArglist[i]);
            params.append(s);
        }
        LocalFree(szArglist);

        while (params.count() > 0) {
            err = processOneParam(&params);
            if (!err.isEmpty())
                break;
        }
    }

    return err;
}

bool CommandLine::isPresent(const QString& name)
{
    bool r = false;
    for (int i = 0; i < this->parsedOptions.count(); i++) {
        ParsedOption* po = this->parsedOptions.at(i);
        if (po->opt && po->opt->nameMatches(name)) {
            r = true;
            break;
        }
    }
    return r;
}

QString CommandLine::get(const QString& name) const
{
    QString r;
    for (int i = 0; i < this->parsedOptions.count(); i++) {
        ParsedOption* po = this->parsedOptions.at(i);
        if (po->opt && po->opt->nameMatches(name)) {
            r = po->value;
            break;
        }
    }
    return r;
}

QList<CommandLine::ParsedOption *> CommandLine::getParsedOptions() const
{
    return this->parsedOptions;
}

bool CommandLine::argumentsAvailable() const
{
    return this->parsedOptions.size() > 0;
}

QStringList CommandLine::getAll(const QString& name) const
{
    QStringList r;
    for (int i = 0; i < this->parsedOptions.count(); i++) {
        ParsedOption* po = this->parsedOptions.at(i);
        if (po->opt && po->opt->nameMatches(name)) {
            r.append(po->value);
        }
    }
    return r;
}

