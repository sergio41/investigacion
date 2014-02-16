#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "binarytreenode.h"
#include "binarytree.h"
#include "generadorvariables.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void imprimir(QString cosa);

private slots:
    void on_lineEdit_textChanged();

    void on_pBAnadir_clicked();


    void on_listViewSet_clicked(const QModelIndex &index);

    void on_pBClearSET_clicked();

    void on_pBDeleteSET_clicked();

    QString imprimirNodo(BinaryTreeNode *actual);

    void on_actionLog_triggered(bool checked);

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
