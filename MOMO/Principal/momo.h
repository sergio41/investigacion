#ifndef MOMO_H
#define MOMO_H

#include <QMainWindow>

namespace Ui {
class MOMO;
}

class MOMO : public QMainWindow
{
    Q_OBJECT

public:
    explicit MOMO(QWidget *parent = 0);
    ~MOMO();

private:
    Ui::MOMO *ui;
};

#endif // MOMO_H
