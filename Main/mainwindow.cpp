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
    docContr.AddCommand("delete",new DeleteDoc());
    docContr.AddCommand("clear",new ClearDoc());

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

    connect(docContr.getCurrentDoc(),&Document::ChangeData,[=](QVector<QString> &Text){ShowTextEdit(Text,ui->OutView);});
    connect(ui->OutView,&QTextEdit::textChanged,docContr.getCurrentDoc(),[=](){docContr.SetNewDataDoc(ui->OutView->toPlainText());});

    connect(ui->tabWidget,&QTabWidget::tabBarClicked,[=](int index){docContr.setCurrentDoc(index);});
    connect(ui->tabWidget,&QTabWidget::tabCloseRequested,[=](int index){DeleteTab(index);});

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

void MainWindow::ShowTextEdit(QVector<QString> &Text,QTextEdit *ptrTextEdit)
{
    QString buf="";
    for(auto line: Text)
    buf+=line+"\n";
    ptrTextEdit->setText(buf);
}



void MainWindow::on_pushButton_clicked()
{
    NewTab(new Document());
}
void MainWindow::DeleteTab(int index)
{
    docContr.setCurrentDoc(index);
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Test", "Save doc ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)
          docContr.AddExecCommand("write");
    docContr.PopDoc(index);
    ui->tabWidget->removeTab(index);
}
void MainWindow::NewTab(Document *newDoc)
{
    QRect geom(30,0,311,221);
    QTextEdit *newTabEdit=new QTextEdit();
    QTabWidget *uiTabWidget=ui->tabWidget;
    newTabEdit->setGeometry(geom);
    docContr.AddDoc(newDoc);
    connect(docContr.getCurrentDoc(),&Document::ChangeData,[=](QVector<QString> &Text){ShowTextEdit(Text,newTabEdit);});
    connect(newTabEdit,&QTextEdit::textChanged,docContr.getCurrentDoc(),[=](){docContr.SetNewDataDoc(newTabEdit->toPlainText());});
    uiTabWidget->addTab(newTabEdit,newDoc->getName());
    uiTabWidget->setCurrentWidget(newTabEdit);

}
