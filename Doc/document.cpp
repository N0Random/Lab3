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
    Name = _Path.right(_Path.length()-indexLastSpliter);
    Path = _Path.left(indexLastSpliter);
}

QVector<QString> Document::getData() const
{

    return Data;
}

void Document::setData(const QVector<QString> &_Data)
{
    Changed=true;
    Data = _Data;
    emit ChangeData(Data);
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
    Name="";
}

Document::Document(QString _Path)
{
    setPath(_Path);
    Data.reserve(100);
}
