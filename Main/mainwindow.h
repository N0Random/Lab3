#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileSystemModel>
#include <QMainWindow>
#include <qtextedit.h>
#include "Doc/doccommands.h"
#include "doccontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();



private:
   DocController docContr;
   QFileSystemModel *model;
   Ui::MainWindow *ui;
   void ShowTextEdit(QVector<QString> &Text,QTextEdit *ptrTextEdit);
   void NewTab(Document *newDoc);
   void OpenFile();
   void DeleteTab(int index);
};

#endif // MAINWINDOW_H
