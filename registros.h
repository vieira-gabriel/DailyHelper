#ifndef REGISTROS_H
#define REGISTROS_H

#include "tasktype.h"
#include <QDialog>

namespace Ui {
class Registros;
}

class Registros : public QDialog {
  Q_OBJECT

public:
  explicit Registros(QWidget *parent = nullptr);
  ~Registros();
  void setTasks(QVector<TaskType> &);
  void loadTasks();

private slots:
  void on_edit_bt_clicked();

private:
  Ui::Registros *ui;

  QVector<TaskType> tasks;
  enum TasksColumns { TITLE, RESUME, TIME };
};

#endif // REGISTROS_H
