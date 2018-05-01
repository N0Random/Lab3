#include "doccontroller.h"

#include <qdir.h>


void DocController::AddExecCommand(QString NameCom)
{
    if(mapComands.contains(NameCom))
    {
        QueueCom.enqueue(NameCom);
        emit addQueueCom();
    }
}

Document *DocController::getCurrentDoc() const
{
    return CurrentDoc;
}

void DocController::setCurrentDoc(Document *value)
{
    CurrentDoc = value;
    for(auto iter:mapComands)
        iter->setDoc(*value);
}

QList<Document *> DocController::getAllDoc() const
{
    return AllDoc;
}

DocController::DocController()
{
    QDir dir;
    QString name=dir.absolutePath()+"/new_doc.txt";
    CurrentDoc=new Document(name);
    connect(this,&DocController::addQueueCom,&DocController::DoCommand);
}

void DocController::AddCommand(QString NameCom, IDocCommands *Com)
{
    if(!mapComands.contains(NameCom) )
        mapComands[NameCom]=Com;
}

void DocController::DoCommand()
{
    while(!QueueCom.isEmpty())
    {
        QString NameCommande = QueueCom.dequeue();
        if(mapComands.contains(NameCommande) and CurrentDoc)
        {
            mapComands[NameCommande]->execute();
            logCommands.append(NameCommande+":"+CurrentDoc->getName());
        }
    }
}

void DocController::AddDoc(Document *Doc)
{
    AllDoc.append(Doc);
    setCurrentDoc(Doc);
}
