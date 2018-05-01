#ifndef DOCCOMMANDS_H
#define DOCCOMMANDS_H
#include "document.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

class IDocCommands
{
protected:
    Document *doc;
public:
    IDocCommands(Document &value);
    IDocCommands();
    virtual void execute();
    void setDoc(Document &value);
    Document *getDoc() const;
};

class ReadDoc:public IDocCommands
{
public:
    ReadDoc();
    ReadDoc(Document &Doc);
    void execute();
};
class WriteDoc:public IDocCommands
{
public:
    WriteDoc();
    WriteDoc(Document &value);
    void execute();
};
#endif // DOCCOMMANDS_H
