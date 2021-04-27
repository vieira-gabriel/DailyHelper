#include "registros.h"
#include "ui_registros.h"

Registros::Registros(QWidget *parent) : QDialog(parent), ui(new Ui::Registros) {
  ui->setupUi(this);
}

Registros::~Registros() { delete ui; }

void Registros::setTasks(QVector<TaskType> &tasks) {
  this->tasks = tasks;
  //  for (int i = 0; i < tasks.size(); i++) {
  //    TaskType new_task(tasks[i]);
  //    this->tasks.append(new_task);
  //  }
}

void Registros::on_edit_bt_clicked() {}
