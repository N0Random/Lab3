#ifndef DOCCONTROLLER_H
#define DOCCONTROLLER_H
#include "Doc/doccommands.h"

#include <QQueue>
#include <QObject>

class DocController: public QObject
{
    Q_OBJECT
private:
    QList<Document *> AllDoc;
    Document *CurrentDoc;
    QMap<QString,IDocCommands*> mapComands;
    QQueue<QString> QueueCom;
    QList<QString> logCommands;
public:

    DocController();
    void AddCommand(QString NameCom,IDocCommands* Com);
    void DoCommand();
    void AddDoc(Document* Doc);
    void AddExecCommand(QString NameCom);
    void SetNewDataDoc(QString newData);
    void PopDoc(int index);
    Document *getCurrentDoc() const;
    void setCurrentDoc(Document *value);
    void setCurrentDoc(int index);
    QList<Document *> getAllDoc() const;

signals:
    void addQueueCom();
};

#endif // DOCCONTROLLER_H
