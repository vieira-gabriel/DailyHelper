#include "registros.h"
#include "ui_registros.h"

Registros::Registros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registros)
{
    ui->setupUi(this);
}

Registros::~Registros()
{
    delete ui;
}
