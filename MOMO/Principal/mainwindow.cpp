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
#include <QFileDialog>
#include <QXmlStreamWriter>

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
    QString retorno;
    parser aux = parser();
    if (aux.comprobarParser(ui->lineEdit->text())) {
        QStandardItem* Items = new QStandardItem(ui->lineEdit->text());
        model->appendRow(Items);
        almacenador aux1 = almacenador();
        LBinaryTree arbol = aux1.almacenar(ui->lineEdit->text());
        if(arbol.getFirst()->GetChar()!=""){
          anadirADepurador(arbol.getFirst()->GetChar());
          retorno = arbol.getFirst()->GetChar();
          if(arbol.getFirst()->GetLeftChild()!=NULL){
              retorno = imprimirNodo(arbol.getFirst()->GetLeftChild()) + retorno;
          }
          if(arbol.getFirst()->GetRightChild()!=NULL){
              retorno = retorno + imprimirNodo(arbol.getFirst()->GetRightChild());
          }
          anadirADepurador(retorno);
        }
        LBinaryTree arbol2= aux1.nnf(arbol);
        if(arbol2.getFirst()->GetChar()!=""){
          anadirADepurador(arbol2.getFirst()->GetChar());
          retorno = arbol2.getFirst()->GetChar();
          //QMessageBox::warning(this, "Warning:", arbol2.getFirst()->GetChar(), QMessageBox::Ok);
          if(arbol2.getFirst()->GetLeftChild()!=NULL){
              retorno = imprimirNodo(arbol2.getFirst()->GetLeftChild()) + retorno;
          }
          if(arbol2.getFirst()->GetRightChild()!=NULL){
              retorno = retorno + imprimirNodo(arbol2.getFirst()->GetRightChild());
          }
          anadirADepurador(retorno);
        }
        LBinaryTree arbol3= aux1.dtnf(arbol2);
        if(arbol3.getFirst()->GetChar()!=""){
          anadirADepurador(arbol3.getFirst()->GetChar());
          retorno = arbol3.getFirst()->GetChar();
          //QMessageBox::warning(this, "Warning:", arbol3.getFirst()->GetChar(), QMessageBox::Ok);
          if(arbol3.getFirst()->GetLeftChild()!=NULL){
              retorno = imprimirNodo(arbol3.getFirst()->GetLeftChild()) + retorno;
          }
          if(arbol3.getFirst()->GetRightChild()!=NULL){
              retorno = retorno + imprimirNodo(arbol3.getFirst()->GetRightChild());
          }
          anadirADepurador(retorno);
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

QString MainWindow::imprimirNodo(BinaryTreeNode *actual){
    anadirADepurador(actual->GetChar());
    QString retorno = actual->GetChar();
    if(actual->GetLeftChild()!=NULL){
            retorno = imprimirNodo(actual->GetLeftChild()) + retorno;
    }
    if(actual->GetRightChild()!=NULL){
        retorno = retorno + imprimirNodo(actual->GetRightChild());
    }
    if(actual->GetChar()==QString(SimbAND)||actual->GetChar()==QString(SimbOR)
            ||actual->GetChar()==QString(SimbUNTIL)||actual->GetChar()==QString(SimbRELEASE)
            ||actual->GetChar()==QString(SimbINPIZQ)||actual->GetChar()==QString(SimbINPDER)
            ||actual->GetChar()==QString(SimbSSS))
        retorno = QString("(")+retorno+QString(")");
    return retorno;
}

void MainWindow::on_actionLog_triggered(bool checked)
{
    if (checked) iniciarDepurador();
    else terminarDepurador();
}



void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir proyecto"), "", tr("Momo proyect (*.momo)"));



    QFile * xmlFile = new QFile(fileName);
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this,"Load XML File Problem",
        "Couldn't open xmlfile.xml to load settings for download",
        QMessageBox::Ok);
        return;
    } else {
        QXmlStreamReader * xmlReader = new QXmlStreamReader(xmlFile);

        //Parse the XML until we reach end of it
        while(!xmlReader->atEnd() && !xmlReader->hasError()) {

            // Read next element
            QXmlStreamReader::TokenType token = xmlReader->readNext();
            //If token is just StartDocument - go to next
            if(token == QXmlStreamReader::StartDocument) continue;
            //If token is StartElement - read it
            if(token == QXmlStreamReader::StartElement) {
                if(xmlReader->name() == "MOMO") continue;
                if(xmlReader->name() == "version") continue;
                if(xmlReader->name() == "FORMULAS") continue;
                if(xmlReader->name() == "FORMULA") continue;
                if(xmlReader->name() == "form") {
                    ui->lineEdit->setText(xmlReader->readElementText());
                    on_pBAnadir_clicked();
                }
            }
        }

        if(xmlReader->hasError()) {
                QMessageBox::critical(this,
                "xmlFile.xml Parse Error",xmlReader->errorString(),
                QMessageBox::Ok);
                return;
        }

        //close reader and flush file
        xmlReader->clear();
        xmlFile->close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Momo proyect"), "", tr("Momo proyect (*.momo)"));
    if (fileName.isEmpty())
        ;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        else {
            QXmlStreamWriter xmlWriter(&file);

            xmlWriter.setAutoFormatting(true);

            xmlWriter.writeStartDocument();

                xmlWriter.writeStartElement("MOMO");
                    xmlWriter.writeTextElement("version","1.0");
                    xmlWriter.writeStartElement("FORMULAS");

                        for (int row = 0; row < model->rowCount(); row++ ) {
                            QStandardItem* Item = model->item(row, 0);
                            xmlWriter.writeStartElement("FORMULA");
                            xmlWriter.writeTextElement("form", Item->text());
                            xmlWriter.writeEndElement();
                        }

                    xmlWriter.writeEndElement();
                xmlWriter.writeEndElement();

            xmlWriter.writeEndDocument();
            file.close();
        }
    }
}