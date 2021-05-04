#include "registros.h"
#include "edit_task.h"
#include "ui_registros.h"
#include <QAbstractItemModel>
#include <QDebug>
#include <QMessageBox>

Registros::Registros(QWidget *parent) : QDialog(parent), ui(new Ui::Registros) {
  ui->setupUi(this);

  QStringList columns;
  columns << "ID"
          << "Título"
          << "Resumo"
          << "Tempo investido";
  ui->tableWidget->setColumnCount(4);
  ui->tableWidget->setHorizontalHeaderLabels(columns);
  ui->tableWidget->setColumnWidth(ID, 50);
  ui->tableWidget->setColumnWidth(TITLE, 200);
  ui->tableWidget->setColumnWidth(RESUME, 350);
  ui->tableWidget->setColumnWidth(TIME, 150);
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableWidget->verticalHeader()->setVisible(false);
}

Registros::~Registros() { delete ui; }

void Registros::loadTasks() {

  QSqlQuery query;

  qDebug() << "Carregando tasks table";

  if (query.exec("SELECT * FROM Tasks")) {
    for (int row = 0; query.next(); ++row) {
      ui->tableWidget->insertRow(row);
      ui->tableWidget->setItem(
          row, ID, new QTableWidgetItem(query.value(ID).toString()));
      ui->tableWidget->setItem(
          row, TITLE, new QTableWidgetItem(query.value(TITLE).toString()));
      ui->tableWidget->setItem(
          row, RESUME, new QTableWidgetItem(query.value(RESUME).toString()));
      ui->tableWidget->setItem(
          row, TIME, new QTableWidgetItem(query.value(TIME).toString()));
    }
  } else {
    QMessageBox::warning(this, "ERRO",
                         "Erro ao pesquisar na tabela de contatos");
    qDebug() << query.lastError().text();
  }

  ui->tableWidget->show();
}

void Registros::on_edit_bt_clicked() {
  int row = ui->tableWidget->currentRow();
  int id = ui->tableWidget->item(row, 0)->text().toInt();
  edit_task f_edit_task(this, id);
  f_edit_task.exec();

  QSqlQuery query;
  qDebug() << "Atualizando a tabela de tarefas";

  query.prepare("SELECT * FROM Tasks WHERE id = :id");
  query.bindValue(":id", id);
  if (query.exec()) {
    query.first();
    ui->tableWidget->setItem(
        row, TITLE, new QTableWidgetItem(query.value(TITLE).toString()));
    ui->tableWidget->setItem(
        row, RESUME, new QTableWidgetItem(query.value(RESUME).toString()));
    ui->tableWidget->setItem(
        row, TIME, new QTableWidgetItem(query.value(TIME).toString()));
  } else {
    QMessageBox::warning(this, "ERRO",
                         "Erro ao pesquisar na tabela de contatos");
    qDebug() << query.lastError().text();
  }
}

void Registros::on_pushButton_3_clicked() { this->close(); }

void Registros::on_delete_bt_clicked() {
  int row = ui->tableWidget->currentRow();
  QString task = ui->tableWidget->item(row, 0)->text();

  QSqlQuery query;
  query.prepare("DELETE FROM Tasks WHERE task=:title");
  query.bindValue(":title", task);
  if (query.exec()) {
    QMessageBox::information(this, "", "Registro excluido");

  } else {
    QMessageBox::warning(this, "ERRO", "Erro ao excluir o registro");
    qDebug() << query.lastError().text();
  }
  ui->tableWidget->removeRow(row);
}
