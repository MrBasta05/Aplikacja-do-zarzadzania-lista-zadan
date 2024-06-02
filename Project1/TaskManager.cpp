#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TaskManager.h"
using namespace std;

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

void TaskManager::saveTaskList(const std::string& filename)
const{
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& task : tasks) {
            file << task << "\n";
        }
        file.close();
    }
}

std::vector<Task> TaskManager::getTasks() const {
    return tasks;
}