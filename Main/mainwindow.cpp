#include "mainwindow.h"
#include "Doc/doccommands.h"
#include "ui_mainwindow.h"
#include "iostream"

#include <QDir>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString p="/re.txt";
    QDir dir;
    p=dir.absolutePath()+p;
    Document doc(p);
    ReadDoc read(doc);

    read.execute();
    doc.setChanged(true);
    QVector<QString> buf=doc.getData();
    buf.append("New row");
    doc.setData(buf);
    WriteDoc wr(doc);
    wr.execute();
    for(auto iter:doc.getData())
    {
        std::cout<<iter.toStdString()<<"\n";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
