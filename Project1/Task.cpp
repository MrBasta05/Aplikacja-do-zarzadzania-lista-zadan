#include "Task.h"

Task::Task(std::string title, std::string description, std::string dueDate, std::string priority, std::string category)
    : title(title), description(description), dueDate(dueDate), priority(priority), category(category) {}

std::string Task::getTitle() const {
    return title;
}

void Task::setTitle(const std::string& title) {
    this->title = title;
}

std::string Task::getDescription() const {
    return description;
}

void Task::setDescription(const std::string& description) {
    this->description = description;
}

std::string Task::getDueDate() const {
    return dueDate;
}

void Task::setDueDate(const std::string& dueDate) {
    this->dueDate = dueDate;
}

std::string Task::getPriority() const {
    return priority;
}

void Task::setPriority(const std::string& priority) {
    this->priority = priority;
}

std::string Task::getCategory() const {
    return category;
}

void Task::setCategory(const std::string& category) {
    this->category = category;
}