#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <simbolos.h>
#include "parser.h"
#include "logicaVentana.cpp"
#include "almacenador.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QModelIndex>
#include <QModelIndexList>
#include <QMessageBox>
QStandardItemModel *model ;

#include <iostream>
using namespace std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->listViewSet->setModel(model);
    iniciarDepurador();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged()
{

    simbolos sim;
    ui->lineEdit->setText(sim.pasarDeTextoATextoConSimbolos(ui->lineEdit->text()));
}

void MainWindow::on_pBAnadir_clicked()
{

    parser aux = parser();
    if (aux.comprobarParser(ui->lineEdit->text())) {
        QStandardItem* Items = new QStandardItem(ui->lineEdit->text());
        model->appendRow(Items);
        almacenador aux1 = almacenador();
        LBinaryTree arbol = aux1.almacenar(ui->lineEdit->text());
        if(arbol.getFirst()->GetChar()!=""){
          depurador->Anadir(arbol.getFirst()->GetChar());
          //QMessageBox::warning(this, "Warning:", arbol.getFirst()->GetChar(), QMessageBox::Ok);
          if(arbol.getFirst()->GetLeftChild()!=NULL){
              imprimirNodo(arbol.getFirst()->GetLeftChild());
          }
          if(arbol.getFirst()->GetRightChild()!=NULL){
              imprimirNodo(arbol.getFirst()->GetRightChild());
          }
        }
        LBinaryTree arbol2= aux1.nnf(arbol);
        if(arbol2.getFirst()->GetChar()!=""){
          depurador->Anadir(arbol2.getFirst()->GetChar());
          //QMessageBox::warning(this, "Warning:", arbol2.getFirst()->GetChar(), QMessageBox::Ok);
          if(arbol2.getFirst()->GetLeftChild()!=NULL){
              imprimirNodo(arbol2.getFirst()->GetLeftChild());
          }
          if(arbol2.getFirst()->GetRightChild()!=NULL){
              imprimirNodo(arbol2.getFirst()->GetRightChild());
          }
        }
        LBinaryTree arbol3= aux1.dtnf(arbol2);
        if(arbol3.getFirst()->GetChar()!=""){
          depurador->Anadir(arbol3.getFirst()->GetChar());
          //QMessageBox::warning(this, "Warning:", arbol3.getFirst()->GetChar(), QMessageBox::Ok);
          if(arbol3.getFirst()->GetLeftChild()!=NULL){
              imprimirNodo(arbol3.getFirst()->GetLeftChild());
          }
          if(arbol3.getFirst()->GetRightChild()!=NULL){
              imprimirNodo(arbol3.getFirst()->GetRightChild());
          }
        }
    } else {
        QMessageBox::warning(this, "Warning:", "Formula not valid", QMessageBox::Ok);
    }
}

void MainWindow::imprimir(QString cosa){
     QMessageBox::warning(this, "Warning:", cosa, QMessageBox::Ok);
}

void MainWindow::on_listViewSet_clicked(const QModelIndex &index)
{
   QStandardItem* Items = model->item(index.row(),0);
   ui->lineEdit->setText(Items->text());
}

void MainWindow::on_pBClearSET_clicked()
{
    model->clear();
}

void MainWindow::on_pBDeleteSET_clicked()
{
    QModelIndexList indexes = ui->listViewSet->selectionModel()->selectedIndexes();
    foreach (QModelIndex index, indexes) {
        model->removeRow(index.row());
    }
}

void MainWindow::imprimirNodo(BinaryTreeNode *actual){
    //QMessageBox::warning(this, "Warning:", actual->GetChar(), QMessageBox::Ok);
    depurador->Anadir(actual->GetChar());
    if(actual->GetLeftChild()!=NULL){
        imprimirNodo(actual->GetLeftChild());
    }
    if(actual->GetRightChild()!=NULL){
        imprimirNodo(actual->GetRightChild());
    }
}
