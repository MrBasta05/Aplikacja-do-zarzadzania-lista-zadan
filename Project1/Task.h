#pragma once
#ifndef TASK_H
#define TASK_H
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Task {
private:
    std::string title;
    std::string description;
    std::string dueDate;
    std::string priority;
    std::string category;

public:
    Task(std::string title, std::string description, std::string dueDate, std::string priority, std::string category);

    // Gettery i settery
    std::string getTitle() const;
    void setTitle(const std::string& title);

    std::string getDescription() const;
    void setDescription(const std::string& description);

    std::string getDueDate() const;
    void setDueDate(const std::string& dueDate);

    std::string getPriority() const;
    void setPriority(const std::string& priority);

    std::string getCategory() const;
    void setCategory(const std::string& category);
    //save format
    friend std::ostream& operator<<(std::ostream& os, const Task& task) {
        os << "Task Name: " << task.title << "\n";
        os << "Task Name: " << task.description << "\n";
        os << "Task Name: " << task.dueDate << "\n";
        os << "Task Name: " << task.category << "\n";
        os << "Priority: " << task.priority << "\n";
        return os;
    }
 
};

#endif // TASK_H