#include "document.h"

QString Document::getPath() const
{
    return Path;
}

void Document::setPath(const QString &_Path)
{
    Path = _Path;
}

QVector<QString> Document::getData() const
{

    return Data;
}

void Document::setData(const QVector<QString> &_Data)
{
    Data = _Data;
}

QString Document::getFormate() const
{
    return Formate;
}

void Document::setFormate(const QString &_Formate)
{
    Formate = _Formate;
}

void Document::setChanged(bool _Changed)
{
    Changed = _Changed;
}

bool Document::getChanged() const
{
    return Changed;
}

Document::Document()
{
    Path="";
    Data.reserve(100);
    Formate="";
}

Document::Document(QString _Path)
{
    Path = _Path;
    Data.reserve(100);
    Formate = "";
}
