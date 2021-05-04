#ifndef EDIT_TASK_H
#define EDIT_TASK_H

#include <QDialog>

namespace Ui {
class edit_task;
}

class edit_task : public QDialog {
  Q_OBJECT

public:
  explicit edit_task(QWidget *parent = nullptr, int id = 0);
  ~edit_task();

private slots:
  void on_cancel_bt_clicked();

  void on_save_bt_clicked();

private:
  Ui::edit_task *ui;
  int id;
  enum TasksColumns { ID, TITLE, RESUME, TIME };
};

#endif // EDIT_TASK_H
