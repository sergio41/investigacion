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
    QTime time = QTime::currentTime();
    QString timeString = time.toString();

    QString aux = ui->textEdit->toPlainText() + "\n" + time.toString() + ": " + texto;
    ui->textEdit->setText(aux);
}
