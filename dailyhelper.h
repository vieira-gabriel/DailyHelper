#ifndef DAILYHELPER_H
#define DAILYHELPER_H

#include "registros.h"
#include "tasktype.h"
#include <QMainWindow>

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

  QVector<TaskType> tasks;
};
#endif // DAILYHELPER_H
