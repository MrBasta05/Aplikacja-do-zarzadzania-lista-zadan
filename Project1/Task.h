#pragma once
#ifndef TASK_H
#define TASK_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
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
        os << task.title <<"~" << task.description << "~" << task.dueDate << "~" << task.category << "~" << task.priority << "\n";
        return os;
    }
    //read format
    static Task fromStream(std::istream& is) {
        std::string title, description, dueDate, priority, category;
        std::string line;

        if (std::getline(is, line)) {
            std::istringstream lineStream(line);
            std::getline(lineStream, title, '~');
            std::getline(lineStream, description, '~');
            std::getline(lineStream, dueDate, '~');
            std::getline(lineStream, category, '~');
            std::getline(lineStream, priority, '~');
        }

        return Task(title, description, dueDate, priority, category);
    };
 
};

#endif // TASK_H