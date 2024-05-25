#pragma once
#ifndef TASK_H
#define TASK_H

#include <string>

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
};

#endif // TASK_H