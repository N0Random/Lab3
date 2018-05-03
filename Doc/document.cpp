#include "document.h"

QString Document::getPath() const
{
    return Path;
}

void Document::setPath(const QString &_Path)
{
    int indexLastSpliter=0;
    if( _Path.contains('/'))
        indexLastSpliter=_Path.lastIndexOf('/');
    Name = _Path.right(_Path.length()-indexLastSpliter-1);
    Path = _Path.left(indexLastSpliter+1);
}

QVector<QString> Document::getData() const
{

    return Data;
}

void Document::setData(const QVector<QString> &_Data)
{
    Data = _Data; 
}

void Document::setChanged(bool _Changed)
{
    Changed = _Changed;
}

bool Document::getChanged() const
{
    return Changed;
}

QString Document::getName() const
{
    return Name;
}

void Document::setName(const QString &value)
{
    Name = value;
}

Document::Document()
{
    Path="";
    Data.reserve(100);
    Name="New.txt";
}

Document::Document(QString _Path)
{
    setPath(_Path);
    Changed=false;
    Data.reserve(100);
}

Document::Document(QString _Path, QVector<QString> _Data)
{
    setPath(_Path);
    Changed=true;
    Data = _Data;
}
