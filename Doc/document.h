#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <QVector>
#include <qstring.h>


class Document
{
private:
    QString Path;
    QVector<QString> Data;
    QString Formate;
    bool Changed;
public:
    Document();
    Document(QString _Path);

    QString getPath() const;
    void setPath(const QString &_Path);
    QVector<QString> getData() const;
    void setData(const QVector<QString> &_Data);
    QString getFormate() const;
    void setFormate(const QString &_Formate);
    void setChanged(bool Changed);
    bool getChanged() const;
};

#endif // DOCUMENT_H
