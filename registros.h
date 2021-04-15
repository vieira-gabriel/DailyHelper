#ifndef REGISTROS_H
#define REGISTROS_H

#include <QDialog>

namespace Ui {
class Registros;
}

class Registros : public QDialog
{
    Q_OBJECT

public:
    explicit Registros(QWidget *parent = nullptr);
    ~Registros();

private:
    Ui::Registros *ui;
};

#endif // REGISTROS_H
