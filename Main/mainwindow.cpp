#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

#include <QDir>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);



    NewTab(new Document());
    connect(ui->tabWidget,&QTabWidget::tabBarClicked,[=](int index){docContr.setCurrentDoc(index);});
    connect(ui->tabWidget,&QTabWidget::tabCloseRequested,[=](int index){DeleteTab(index);});

    connect(ui->aNewFile,&QAction::triggered,[=](){NewTab(new Document());});
    connect(ui->aOpenFile,&QAction::triggered,[=](){OpenFile();});
    connect(ui->aSaveFile,&QAction::triggered,[=](){docContr.AddExecCommand("write");});


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowTextEdit(QVector<QString> &Text,QTextEdit *ptrTextEdit)
{
    QString buf="";
    for(auto line: Text)
    buf+=line+"\n";
    ptrTextEdit->setText(buf);
}



void MainWindow::on_pushButton_clicked()
{
   docContr.AddExecCommand("clear");
}
void MainWindow::DeleteTab(int index)
{

    docContr.setCurrentDoc(index);
    if(docContr.getCurrentDoc()->getChanged())
        {
        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Test", "Save doc ?",
                                        QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes)
              docContr.AddExecCommand("write");
         }
    if(ui->tabWidget->count()==1)
          NewTab(new Document());
    docContr.PopDoc(index);   
    if(index)
        ui->tabWidget->setCurrentIndex(index-1);
    ui->tabWidget->removeTab(index);

}
void MainWindow::NewTab(Document *newDoc)
{
    QTextEdit *newTabEdit=new QTextEdit();
    QTabWidget *uiTabWidget=ui->tabWidget;
    docContr.AddDoc(newDoc);
    connect(docContr.getCurrentDoc(),&Document::ChangeData,[=](QVector<QString> &Text){ShowTextEdit(Text,newTabEdit);});
    connect(newTabEdit,&QTextEdit::textChanged,docContr.getCurrentDoc(),[=](){docContr.SetNewDataDoc(newTabEdit->toPlainText());});
    uiTabWidget->addTab(newTabEdit,newDoc->getName());
    uiTabWidget->setCurrentWidget(newTabEdit);

}

void MainWindow::OpenFile()
{
     QString filePath= QFileDialog::getOpenFileName(this,"Open file","","");
     if(!filePath.isEmpty())
     {
        NewTab(new Document(filePath));
        docContr.AddExecCommand("read");
     }

}
