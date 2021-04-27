#include "registros.h"
#include "ui_registros.h"
#include <QAbstractItemModel>
#include <QDebug>

Registros::Registros(QWidget *parent) : QDialog(parent), ui(new Ui::Registros) {
  ui->setupUi(this);

  QStringList columns;
  columns << "Título"
          << "Resumo"
          << "Tempo investido";
  ui->tableWidget->setColumnCount(3);
  ui->tableWidget->setHorizontalHeaderLabels(columns);
}

Registros::~Registros() { delete ui; }

void Registros::setTasks(QVector<TaskType> &tasks) {
  this->tasks = tasks;
  //  for (int i = 0; i < tasks.size(); i++) {
  //    TaskType new_task(tasks[i]);
  //    this->tasks.append(new_task);
  //  }
}

void Registros::loadTasks() {
  qDebug() << "Loading tasks table";
  for (int row = 0; row < tasks.size(); ++row) {
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(row, TITLE,
                             new QTableWidgetItem(tasks[row].getTitle()));
    ui->tableWidget->setItem(row, RESUME,
                             new QTableWidgetItem(tasks[row].getResume()));
    ui->tableWidget->setItem(row, TIME,
                             new QTableWidgetItem(tasks[row].getTime()));
  }
  ui->tableWidget->show();
}

void Registros::on_edit_bt_clicked() {}
