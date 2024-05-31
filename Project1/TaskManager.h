#pragma once
#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <vector>
#include "Task.h"

class TaskManager {
private:
    std::vector<Task> tasks;

public:
    void addTask(const Task& task);
    void editTask(int index, const Task& task);
    void deleteTask(int index);
    std::vector<Task> getTasks() const;
    std::vector<Task> getSortedTasks() const;
};

#endif // TASKMANAGER_H