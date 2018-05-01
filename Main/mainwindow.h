#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileSystemModel>
#include <QMainWindow>
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
    void ShowTextEdit(QVector<QString> &Text);

private:
   DocController docContr;
   void DoCommand(QString NameCommande);
   QMap<QString,IDocCommands*> mapComands;
   QList<IDocCommands> logCommands;
   QFileSystemModel *model;
   Document *doc;
   Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
