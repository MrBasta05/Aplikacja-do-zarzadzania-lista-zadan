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
    vector<Task> sortedTasks = getSortedTasks();
    if (index >= 0 && index < sortedTasks.size()) {
        sortedTasks[index] = task;
        tasks = sortedTasks;
    }
}

void TaskManager::deleteTask(int index) {
    vector<Task> sortedTasks = getSortedTasks();
    if (index >= 0 && index < sortedTasks.size()) {
        sortedTasks.erase(sortedTasks.begin() + index);
        tasks = sortedTasks;
    }
}

void TaskManager::saveTaskList(const std::string& filename)
const{
    std::ofstream file(filename);
    if (file.is_open()) {
        vector<Task> sortedTasks = getSortedTasks();
        reverse(sortedTasks.begin(), sortedTasks.end());
        for (const auto& task : sortedTasks) {
            file << task << "\n";
        }
        file.close();
    }
}

void TaskManager::loadTasksFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        tasks.clear();
        while (!file.eof()) {
            Task task = Task::fromStream(file);
            if (!task.getTitle().empty()) { 
                tasks.push_back(task);
            }
        }
        file.close();
    }
}

std::vector<Task> TaskManager::getSortedTasks() const {
	std::vector<Task> sortedTasks = tasks;
	std::sort(sortedTasks.begin(), sortedTasks.end(), [](const Task& a, const Task& b) {
		return std::stoi(a.getPriority()) > std::stoi(b.getPriority());
		});

	return sortedTasks;
}