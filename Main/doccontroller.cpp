#include "doccontroller.h"

#include <QDateTime>
#include <qdir.h>


void DocController::AddExecCommand(QString NameCom)
{
    if(mapComands.contains(NameCom))
    {
        QueueCom.enqueue(NameCom);
        emit addQueueCom();
    }
}

void DocController::SetNewDataDoc(QString newData)
{
    QVector<QString> buf;
     for(auto line:newData.split("\n"))
            buf.append(line);
    CurrentDoc->setData(buf);
    CurrentDoc->setChanged(true);
}

void DocController::PopDoc(int index)
{
    if(index )
          setCurrentDoc(index-1);
    else
          setCurrentDoc(index+1);
    AllDoc.removeAt(index);
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

void DocController::setCurrentDoc(int index)
{

    CurrentDoc=AllDoc.at(index);
    for(auto iter:mapComands)
        iter->setDoc(*CurrentDoc);
}

QList<Document *> DocController::getAllDoc() const
{
    return AllDoc;
}

DocController::DocController()
{
   AddCommand("read",new ReadDoc());
   AddCommand("write",new WriteDoc());
   AddCommand("delete",new DeleteDoc());
   AddCommand("clear",new ClearDoc());
   timeStart=QDateTime::currentDateTimeUtc();
   QDir dir;
   QString name=dir.absolutePath()+"/new_doc.txt";
   CurrentDoc=new Document(name);
   connect(this,&DocController::addQueueCom,&DocController::DoCommand);
}

DocController::~DocController()
{
    if(!logCommands.isEmpty())
    {
        QDir dir;
        QString name=dir.absolutePath()+"/Log/log_("+timeStart.toString("ddMMyyyy_hhmmss")+"-"
                +QDateTime::currentDateTimeUtc().toString("ddMMyyyy_hhmmss")+").txt";
        AddDoc(new Document(name,logCommands));
        AddExecCommand("write");
    }
    for(auto iter : AllDoc)
        delete iter;
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
            logCommands.append("<"+NameCommande+":"+CurrentDoc->getName()+"; \n Path:"
                               +CurrentDoc->getPath()+"; \n Time:"
                               +QDateTime::currentDateTime().toString()+"> \n");
        }
    }
}

void DocController::AddDoc(Document *Doc)
{
    AllDoc.append(Doc);
    setCurrentDoc(Doc);
}
