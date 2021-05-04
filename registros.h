#ifndef REGISTROS_H
#define REGISTROS_H

#include <QDialog>
#include <QDir>
#include <QtSql>

namespace Ui {
class Registros;
}

class Registros : public QDialog {
  Q_OBJECT

public:
  explicit Registros(QWidget *parent = nullptr);
  ~Registros();
  void loadTasks();

private slots:
  void on_edit_bt_clicked();

  void on_pushButton_3_clicked();

  void on_delete_bt_clicked();

private:
  Ui::Registros *ui;

  QDir database_dir;
  QSqlDatabase database;
  enum TasksColumns { ID, TITLE, RESUME, TIME };
};

#endif // REGISTROS_H
