#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

#include <QDir>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    docContr.AddCommand("read",new ReadDoc());
    docContr.AddCommand("write",new WriteDoc());
    model = new QFileSystemModel();
    model->setRootPath(QDir::currentPath());
    ui->treeView->setModel(model);
    for (int i=1;i<model->columnCount();i++)
        ui->treeView->hideColumn(i);

    QString p="/re.txt";
    QDir dir;
    p=dir.absolutePath()+p;
    doc=new Document(p);
    docContr.AddDoc(doc);
     connect(docContr.getCurrentDoc(),&Document::ChangeData,this,&MainWindow::ShowTextEdit);
    docContr.AddExecCommand("read");

    for(auto iter:docContr.getCurrentDoc()->getData())
    {
        std::cout<<iter.toStdString()<<"\n";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowTextEdit(QVector<QString> &Text)
{
    QString buf="";
    for(auto line: Text)
        buf+=line+"\n";
    ui->OutView->setText(buf);
}


