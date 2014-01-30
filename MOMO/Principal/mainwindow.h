#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "binarytreenode.h"
#include "binarytree.h"

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

    void imprimirNodo(BinaryTreeNode *actual);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
