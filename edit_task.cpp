#include "edit_task.h"
#include "ui_edit_task.h"
#include <QMessageBox>
#include <QtSql>

edit_task::edit_task(QWidget *parent, int id)
    : QDialog(parent), ui(new Ui::edit_task) {
  ui->setupUi(this);
  QSqlQuery query;
  query.prepare("SELECT * FROM Tasks WHERE id = :id");
  query.bindValue(":id", id);
  if (query.exec()) {
    query.first();
    this->id = query.value(ID).toInt();
    ui->title_edit->setText(query.value(TITLE).toString());
    ui->resume_edit->setText(query.value(RESUME).toString());
    ui->time_edit->setText(query.value(TIME).toString());
  } else {
    QMessageBox::warning(this, "ERRO", "Erro ao selecionar tarefa");
    qDebug() << query.lastError().text();
  }
}

edit_task::~edit_task() { delete ui; }

void edit_task::on_cancel_bt_clicked() { this->close(); }

void edit_task::on_save_bt_clicked() {
  QString title = ui->title_edit->text();
  QString resume = ui->resume_edit->toPlainText();
  float time = ui->time_edit->text().toFloat();

  QSqlQuery query;
  query.prepare("UPDATE Tasks SET task = :title, resume = :resume, time = "
                ":time WHERE id = :id");
  query.bindValue(":title", title);
  query.bindValue(":resume", resume);
  query.bindValue(":time", time);
  query.bindValue(":id", this->id);

  if (query.exec()) {
    this->close();
  } else {
    QMessageBox::warning(this, "ERRO", "Erro ao atualizar tarefa");
    qDebug() << query.lastError().text();
  }
}
