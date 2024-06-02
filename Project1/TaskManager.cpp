#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TaskManager.h"
#include <algorithm>

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

std::vector<Task> TaskManager::getSortedTasks() const {
	std::vector<Task> sortedTasks = tasks;
	std::sort(sortedTasks.begin(), sortedTasks.end(), [](const Task& a, const Task& b) {
		return std::stoi(a.getPriority()) > std::stoi(b.getPriority());
		});

	return sortedTasks;
}