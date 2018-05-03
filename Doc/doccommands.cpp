#include "doccommands.h"





IDocCommands::IDocCommands(Document &value)
{
    doc = &value;
}

IDocCommands::IDocCommands()
{

}

void IDocCommands::execute()
{

}

void IDocCommands::setDoc(Document &value)
{
    doc = &value;
}

Document *IDocCommands::getDoc() const
{
    return doc;
}



ReadDoc::ReadDoc(Document &Doc):IDocCommands(Doc)
{   }
ReadDoc::ReadDoc()
{   }
void ReadDoc::execute()
{
    if((doc->getPath()+doc->getName())=="")
    {
        QMessageBox msgBox;
        msgBox.setText("Empty path to file");
        msgBox.exec();
    }
     QFile file(doc->getPath()+doc->getName());
    try
    {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        QVector<QString> buf;
            while (!in.atEnd())
            { 
                QString line = in.readLine();
                buf.append(line);
            }
         doc->setData(buf);
         emit doc->ChangeData(buf);
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
WriteDoc::WriteDoc()
{    }
void WriteDoc::execute()
{
   if(doc->getChanged())
        {
           QFile file(doc->getPath()+doc->getName());
           file.open(QIODevice::WriteOnly | QIODevice::Text);
           QTextStream outStream(&file);
           for(auto line : doc->getData())
              outStream<<line<<"\n";
           doc->setChanged(false);
           file.close();
       }
}


ClearDoc::ClearDoc(Document &value):IDocCommands(value)
{   }
ClearDoc::ClearDoc()
{    }
void ClearDoc::execute()
{
    QVector<QString> buf;
    doc->setData(buf);
    doc->setChanged(true);
    doc->ChangeData(buf);
}
DeleteDoc::DeleteDoc(Document &value):IDocCommands(value)
{   }
DeleteDoc::DeleteDoc()
{    }
void DeleteDoc::execute()
{
    QFile file(doc->getPath()+doc->getName());
    file.remove();
}
