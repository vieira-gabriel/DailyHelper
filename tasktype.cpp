#include "tasktype.h"

TaskType::TaskType() {}

TaskType::TaskType(const TaskType &task)
    : title(task.title), resume(task.resume), time(task.time) {}

TaskType::TaskType(QString title, QString resume, float time)
    : title(title), resume(resume), time(time) {}

QString TaskType::getTitle() { return title; }
QString TaskType::getResume() { return resume; }
float TaskType::getTime() { return time; }

void TaskType::setTitle(QString title) { this->title = title; }
void TaskType::setResume(QString resume) { this->resume = resume; }
void TaskType::setTime(float time) { this->time = time; }
