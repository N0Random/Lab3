#include "doccommands.h"

#include <QFile>
#include <QTextStream>



void IDocCommands::setDoc(Document &value)
{
    doc = &value;
}

Document *IDocCommands::getDoc() const
{
    return doc;
}

IDocCommands::IDocCommands(Document &value)
{
    doc = &value;
}

void IDocCommands::execute()
{

}



ReadDoc::ReadDoc(Document &value):IDocCommands(value)
{   }

void ReadDoc::execute()
{
    if(doc->getPath()=="")
    {
        QMessageBox msgBox;
        msgBox.setText("Empty path to file");
        msgBox.exec();
    }
     QFile file(doc->getPath());
    try
    {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        QVector<QString> buf=doc->getData();
            while (!in.atEnd())
            { 
                QString line = in.readLine();
                buf.append(line);
            }
         doc->setData(buf);
     }
       catch(...)
    {
        if(file.isOpen())
             file.close();
        QMessageBox msgBox;
        msgBox.setText("Faild: to Read file "+doc->getPath());
        msgBox.exec();
    }
}

WriteDoc::WriteDoc(Document &value):IDocCommands(value)
{   }
void WriteDoc::execute()
{
   if(doc->getChanged())
        {
           QFile file(doc->getPath());
           file.open(QIODevice::WriteOnly | QIODevice::Text);
           QTextStream outStream(&file);
           for(auto line : doc->getData())
              outStream<<line<<"\n";
           doc->setChanged(false);
           file.close();
       }
}
