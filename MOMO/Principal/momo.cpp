#include "momo.h"
#include "ui_momo.h"

MOMO::MOMO(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MOMO)
{
    ui->setupUi(this);
}

MOMO::~MOMO()
{
    delete ui;
}
