#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <QVector>
#include <qstring.h>
#include <QObject>
#include <QFile>
#include <QTextStream>

class Document: public QObject
{
    Q_OBJECT
signals:
    void ChangeData(QVector<QString> &_Data);

private:
    QString Path;
    QVector<QString> Data;

    QString Name;
    bool Changed;
public:
    Document();
    Document(QString _Path);
    Document(QString _Path,QVector<QString> _Data);

    QString getPath() const;
    void setPath(const QString &_Path);
    QVector<QString> getData() const;
    void setData(const QVector<QString> &_Data);

    void setChanged(bool Changed);
    bool getChanged() const;
    QString getName() const;
    void setName(const QString &value);
};

#endif // DOCUMENT_H
