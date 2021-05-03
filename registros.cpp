#include "registros.h"
#include "ui_registros.h"
#include <QAbstractItemModel>
#include <QDebug>
#include <QMessageBox>

Registros::Registros(QWidget *parent) : QDialog(parent), ui(new Ui::Registros) {
  ui->setupUi(this);

  QStringList columns;
  columns << "Título"
          << "Resumo"
          << "Tempo investido";
  ui->tableWidget->setColumnCount(3);
  ui->tableWidget->setHorizontalHeaderLabels(columns);
  ui->tableWidget->setColumnWidth(0, 200);
  ui->tableWidget->setColumnWidth(1, 350);
  ui->tableWidget->setColumnWidth(2, 150);
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableWidget->verticalHeader()->setVisible(false);
  ui->tableWidget->setStyleSheet(
      "QTableView {selection-background-colour:green}");

  QDir dir("../DailyHelper/database");
  database_dir = dir;
  QFile file(database_dir.absolutePath() + "/db_tasks.db");
  if (!file.exists()) {
    qDebug() << "Banco de dados não existe";
  }

  database = QSqlDatabase::addDatabase("QSQLITE");

  database.setDatabaseName(database_dir.absolutePath() + "/db_tasks.db");
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
  if (!database.isOpen()) {
    qDebug() << "Banco de dados está fechado. Abrindo o acesso...";
    if (!database.open()) {
      qDebug() << "Falha ao abrir o banco de dados";
      qDebug() << database.lastError().text();
      return;
    }
  }

  QSqlQuery query;

  qDebug() << "Loading tasks table";

  if (query.exec("SELECT * FROM Tasks")) {
    ui->tableWidget->setColumnCount(3);
    for (int row = 0; query.next(); ++row) {
      ui->tableWidget->insertRow(row);
      ui->tableWidget->setItem(
          row, 0, new QTableWidgetItem(query.value(TITLE).toString()));
      ui->tableWidget->setItem(
          row, 1, new QTableWidgetItem(query.value(RESUME).toString()));
      ui->tableWidget->setItem(
          row, 2, new QTableWidgetItem(query.value(TIME).toString()));
    }
  } else {
    QMessageBox::warning(this, "ERRO",
                         "Erro ao pesquisar na tabela de contatos");
    qDebug() << query.lastError().text();
  }

  ui->tableWidget->show();
  database.close();
}

void Registros::on_edit_bt_clicked() {}

void Registros::on_pushButton_3_clicked() {
  database.close();
  this->close();
}

void Registros::on_delete_bt_clicked() {
  int row = ui->tableWidget->currentRow();
  QString task = ui->tableWidget->item(row, 0)->text();

  if (!database.isOpen()) {
    qDebug() << "Banco de dados está fechado. Abrindo o acesso...";
    if (!database.open()) {
      qDebug() << "Falha ao abrir o banco de dados";
      qDebug() << database.lastError().text();
      return;
    }
  }

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
  database.close();
}
