#ifndef DOCCOMMANDS_H
#define DOCCOMMANDS_H
#include "document.h"
#include <QMessageBox>


class IDocCommands
{
protected:
    Document *doc;
public:
    IDocCommands(Document &value);
    virtual void execute();
    void setDoc(Document &value);
    Document *getDoc() const;
};

class ReadDoc:public IDocCommands
{
public:
    ReadDoc(Document &value);
    void execute();
};
class WriteDoc:public IDocCommands
{
public:
    WriteDoc(Document &value);
    void execute();
};
#endif // DOCCOMMANDS_H
