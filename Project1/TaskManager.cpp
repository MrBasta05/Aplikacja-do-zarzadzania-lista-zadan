#include "TaskManager.h"

void TaskManager::addTask(const Task& task) {
    tasks.push_back(task);
}

void TaskManager::editTask(int index, const Task& task) {
    if (index >= 0 && index < tasks.size()) {
        tasks[index] = task;
    }
}

void TaskManager::deleteTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);
    }
}

std::vector<Task> TaskManager::getTasks() const {
    return tasks;
}