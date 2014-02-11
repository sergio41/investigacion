#include "ventana.h"
#include "ui_ventana.h"
#include <QDateTime>



Ventana::Ventana(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::Anadir(QString texto){
    QString aux = ui->textEdit->toPlainText() + "\n" + QTime::currentTime().toString() + ": " + texto;
    ui->textEdit->setText(aux);
}

void Ventana::Vaciar(){
    ui->textEdit->setText("");
}


