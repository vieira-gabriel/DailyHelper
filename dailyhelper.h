#ifndef DAILYHELPER_H
#define DAILYHELPER_H

#include "registros.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui {
class DailyHelper;
}
QT_END_NAMESPACE

class DailyHelper : public QMainWindow {
  Q_OBJECT

public:
  DailyHelper(QWidget *parent = nullptr);
  ~DailyHelper();

private slots:
  void on_registerButton_clicked();

  void on_reportButton_clicked();

  void on_quitButton_clicked();

private:
  Ui::DailyHelper *ui;
  Registros *registros;

  QDir database_dir;
  QSqlDatabase database;

  enum TasksColumns { ID, TITLE, RESUME, TIME };
};
#endif // DAILYHELPER_H
