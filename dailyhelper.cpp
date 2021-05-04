#include "dailyhelper.h"
#include "ui_dailyhelper.h"

// Função para arredondar o float para duas casas decimais
float round_float(float input) {
  int num_int = (input * 1000) + 5;
  num_int /= 10;
  return (float)(num_int) / 100;
}

// Função que cria o banco de dados, caso ele não exista
void initializeDB(QString path, QSqlDatabase database) {
  database = QSqlDatabase::addDatabase("QSQLITE");

  database.setDatabaseName(path);
  if (!database.open()) {
    qDebug() << "Falha ao criar o banco de dados";
    return;
  }

  QSqlQuery query;
  if (!query.exec("CREATE TABLE IF NOT EXISTS Tasks "
                  " (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                  " task VARCHAR(100) NOT NULL, "
                  " resume VARCHAR(2000),"
                  " time FLOAT(2))")) {
    qDebug() << "Erro ao criar a tabela do banco de dados.";
    qDebug() << query.lastError().text();
    return;
  }

  database.close();
}

DailyHelper::DailyHelper(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::DailyHelper) {
  ui->setupUi(this);
  QPixmap logoStone(":/imgs/imgs/stone.png");
  ui->Imagem->setPixmap(logoStone.scaled(100, 100, Qt::KeepAspectRatio));
  ui->dt_Start->setDate(QDate::currentDate());
  ui->dt_End->setDate(QDate::currentDate());

  QDir dir("../DailyHelper");

  if (!dir.cd("database")) {
    dir.mkdir("./database");
    dir.cd("database");
  }

  database_dir = dir;
  QFile file(database_dir.absolutePath() + "/db_tasks.db");
  if (!file.exists()) {
    initializeDB(database_dir.absolutePath() + "/db_tasks.db", database);
  }

  database = QSqlDatabase::addDatabase("QSQLITE");

  database.setDatabaseName(database_dir.absolutePath() + "/db_tasks.db");

  if (!database.open()) {
    qDebug() << "Falha ao abrir o banco de dados";
    return;
  }
}

DailyHelper::~DailyHelper() { delete ui; }

void DailyHelper::on_registerButton_clicked() {
  QString title = ui->txt_title->text();
  QString resume = ui->txt_resume->toPlainText();

  QDateTime startDateTime = ui->dt_Start->dateTime();
  QDateTime finishDateTime = ui->dt_End->dateTime();

  QSqlQuery query;

  bool task_already_exists = false;

  float howLong =
      round_float((float)(startDateTime.secsTo(finishDateTime)) / 3600);

  // Verifica se a tarefa já foi registrada em outro momento. Caso seja, vai
  // somar a hora colocada e atualizar o resumo, caso o usuário deseje
  if (query.exec("SELECT * FROM Tasks")) {
    for (int row = 0; query.next(); ++row) {
      if (query.value(TITLE).toString() == title) {
        task_already_exists = true;
        qDebug() << "Task " + query.value(TITLE).toString() +
                        " already registrated";
        float newTime = query.value(TIME).toFloat();
        howLong += newTime;
        QString lastResume = query.value(RESUME).toString();
        qDebug() << howLong;

        query.prepare("UPDATE Tasks SET time= :time WHERE task= :title");
        query.bindValue(":time", round_float(howLong));
        query.bindValue(":title", title);
        if (!query.exec()) {
          qDebug() << "Erro ao editar valor no banco de dados";
          qDebug() << query.lastError().text();
        } else {
          if (resume != "" && resume != lastResume) {
            QMessageBox::StandardButton answer = QMessageBox::question(
                this, "Resumo diferente", "Deseja sobrescrever o resumo?",
                QMessageBox::Yes | QMessageBox::No);
            if (answer == QMessageBox::Yes) {
              query.exec("UPDATE Tasks SET resume = " + resume +
                         " WHERE title = " + title);
            }
          }
          break;
        }
      }
    }
  } else {
    QMessageBox::warning(this, "ERRO",
                         "Erro ao pesquisar na tabela de contatos");
    qDebug() << query.lastError().text();
  }

  // Cria um novo registro, caso não exista um com o titulo recebido
  if (!task_already_exists && title != "" && resume != "") {
    if (!query.prepare("INSERT INTO Tasks(task, resume, time) VALUES(:task, "
                       ":resume, :time)")) {
      qDebug() << query.lastError().text();
    }
    query.bindValue(":task", title);
    query.bindValue(":resume", resume);
    query.bindValue(":time", howLong);

    if (!query.exec()) {
      qDebug() << "Erro ao inserir valores no banco de dados";
      qDebug() << query.lastError().text();
    }

    ui->txt_title->clear();
    ui->txt_resume->clear();
    ui->dt_Start->setDate(QDate::currentDate());
    ui->dt_End->setDate(QDate::currentDate());
  }
}

void DailyHelper::on_reportButton_clicked() {
  registros = new Registros(this);
  registros->loadTasks();
  registros->show();
}

void DailyHelper::on_quitButton_clicked() {
  database.close();
  this->close();
}
