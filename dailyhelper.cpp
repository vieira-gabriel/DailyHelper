#include "dailyhelper.h"
#include "ui_dailyhelper.h"
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>

float round_float(float input) {
  int num_int = (input * 1000) + 5;
  num_int /= 10;
  return (float)(num_int) / 100;
}

DailyHelper::DailyHelper(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::DailyHelper) {
  ui->setupUi(this);
  QPixmap logoStone(":/imgs/imgs/stone.png");
  ui->Imagem->setPixmap(logoStone.scaled(100, 100, Qt::KeepAspectRatio));
  ui->dt_Start->setDate(QDate::currentDate());
  ui->dt_End->setDate(QDate::currentDate());
}

DailyHelper::~DailyHelper() { delete ui; }

void DailyHelper::on_registerButton_clicked() {
  QString title = ui->txt_title->text();
  QString resume = ui->txt_resume->toPlainText();

  QDateTime startDateTime = ui->dt_Start->dateTime();
  QDateTime finishDateTime = ui->dt_End->dateTime();

  bool already_exists = false;

  float howLong =
      round_float((float)(startDateTime.secsTo(finishDateTime)) / 3600);

  for (int i = 0; i < tasks.size(); ++i) {
    if (tasks[i][0] == title) {
      qDebug() << "Task already registrated";
      time[i] += howLong;
      already_exists = true;
      if (resume != "" && resume != tasks[i][1]) {
        QMessageBox::StandardButton answer = QMessageBox::question(
            this, "Resumo diferente", "Deseja sobrescrever o resumo?",
            QMessageBox::Yes | QMessageBox::No);
        if (answer == QMessageBox::Yes) {
          tasks[i][1] = resume;
        }
      }
      break;
    }
  }

  if (!already_exists) {
    QVector<QString> new_task = {title, resume};
    tasks.append(new_task);
    time.append(howLong);
  }

  qDebug() << tasks[0][0];
  qDebug() << tasks[0][1];
  qDebug() << "Tempo gasto na tarefa: " << time[0];
}

void DailyHelper::on_reportButton_clicked() {
  registros = new Registros(this);
  registros->show();
}

void DailyHelper::on_quitButton_clicked() { this->close(); }
