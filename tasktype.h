#ifndef TASKTYPE_H
#define TASKTYPE_H

#include <QMainWindow>

class TaskType {
public:
  TaskType();
  TaskType(const TaskType &);
  TaskType(QString title, QString resume, float time);

  QString getTitle();
  QString getResume();
  float getTime();

  void setTitle(QString);
  void setResume(QString);
  void setTime(float);

private:
  QString title;
  QString resume;
  float time;
};

#endif // TASKTYPE_H
