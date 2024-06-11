#include "GUI.h"
#include "wx/spinctrl.h"
#include <wx/datectrl.h>



enum {
    ID_AddTask = 1,
    ID_EditTask,
    ID_DeleteTask,
};

GUI::GUI(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 400)) {
    wxPanel* panel = new wxPanel(this, -1);

    taskList = new wxListCtrl(panel, wxID_ANY, wxPoint(10, 10), wxSize(400, 300), wxLC_REPORT | wxLC_SINGLE_SEL);

    taskList->InsertColumn(0, wxT("Title"), wxLIST_FORMAT_LEFT, 160);
    taskList->InsertColumn(1, wxT("Category"), wxLIST_FORMAT_LEFT, 160);
    taskList->InsertColumn(2, wxT("DueDate"), wxLIST_FORMAT_LEFT, 80);
    
    wxStaticText* titleLabel = new wxStaticText(panel, wxID_ANY, wxT("Title:"), wxPoint(420, 10));
    titleInput = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxPoint(500, 10), wxSize(250, 25));

    wxStaticText* descriptionLabel = new wxStaticText(panel, wxID_ANY, wxT("Description:"), wxPoint(420, 50));
    descriptionInput = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxPoint(500, 50), wxSize(250, 105), wxTE_MULTILINE);

    wxStaticText* dueDateLabel = new wxStaticText(panel, wxID_ANY, wxT("Due Date:"), wxPoint(420, 170));
    dueDateInput = new wxDatePickerCtrl(panel, wxID_ANY, wxDefaultDateTime, wxPoint(500, 170), wxSize(250, 25));

    wxStaticText* priorityLabel = new wxStaticText(panel, wxID_ANY, wxT("Priority:"), wxPoint(420, 210));
    priorityInput = new wxSpinCtrl(panel, wxID_ANY, "", wxPoint(500, 210), wxSize(250, 25));


    wxStaticText* categoryLabel = new wxStaticText(panel, wxID_ANY, wxT("Category:"), wxPoint(420, 250));
    wxString categories[] = { wxT("Personal"), wxT("Work"), wxT("Health"), wxT("Finance"), wxT("Education") };
    categoryChoice = new wxChoice(panel, wxID_ANY, wxPoint(500, 250), wxSize(250, 25), WXSIZEOF(categories), categories);
    categoryChoice->SetSelection(0); // Default selection

    wxButton* addButton = new wxButton(panel, ID_AddTask, wxT("Add Task"), wxPoint(450, 290));
    wxButton* editButton = new wxButton(panel, ID_EditTask, wxT("Edit Task"), wxPoint(550, 290));
    wxButton* deleteButton = new wxButton(panel, ID_DeleteTask, wxT("Delete Task"), wxPoint(650, 290));

    Connect(ID_AddTask, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnAddTask));
    Connect(ID_EditTask, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnEditTask));
    Connect(ID_DeleteTask, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnDeleteTask));
    Connect(wxID_ANY, wxEVT_LIST_ITEM_SELECTED, wxCommandEventHandler(GUI::OnSelectTask));
    taskManager.loadTasksFromFile("tasks.txt");
    LoadTasks();
}

void GUI::LoadTasks() {
    taskList->DeleteAllItems();
    const auto& sortedTasks = taskManager.getSortedTasks();

    for (size_t i = 0; i < sortedTasks.size(); ++i) {
        const auto& task = sortedTasks[i];
        wxListItem item;
        item.SetId(i);
        item.SetText(task.getTitle());

        // Set custom background color for different categories
        if (task.getCategory() == "Work") {
            item.SetBackgroundColour(*wxCYAN);
        }
        else if (task.getCategory() == "Education") {
            item.SetBackgroundColour(wxColour(34, 252, 0));
        }
        else if (task.getCategory() == "Health") {
            item.SetBackgroundColour(wxColour(255, 127, 110));
        }
        else if (task.getCategory() == "Finance") {
            item.SetBackgroundColour(*wxYELLOW);
        }
        else if (task.getCategory() == "Personal") {
            item.SetBackgroundColour(*wxLIGHT_GREY);
        }
        else {
            item.SetBackgroundColour(*wxWHITE);
        }

        taskList->InsertItem(item);
        taskList->SetItem(i, 1, task.getCategory());
        taskList->SetItem(i, 2, task.getDueDate());
        titleInput->SetValue("");
        descriptionInput->SetValue("");
        priorityInput->SetValue("");
        categoryChoice->SetStringSelection("");
    }
}

void GUI::OnAddTask(wxCommandEvent& event) {
    std::string title = titleInput->GetValue().ToStdString();
    std::string description = descriptionInput->GetValue().ToStdString();
    std::string dueDate = dueDateInput->GetValue().Format("%d.%m.%G").ToStdString();
    std::string priority = priorityInput->GetTextValue().ToStdString();
    std::string category = categoryChoice->GetStringSelection().ToStdString();

    Task newTask(title, description, dueDate, priority, category);
    taskManager.addTask(newTask);
    taskManager.saveTaskList();
    LoadTasks();
}

void GUI::OnEditTask(wxCommandEvent& event) {
    long selection = taskList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selection == wxNOT_FOUND) return;

    std::string title = titleInput->GetValue().ToStdString();
    std::string description = descriptionInput->GetValue().ToStdString();
    std::string dueDate = dueDateInput->GetValue().Format("%d.%m.%G").ToStdString();
    std::string priority = priorityInput->GetTextValue().ToStdString();
    std::string category = categoryChoice->GetStringSelection().ToStdString();

    Task editedTask(title, description, dueDate, priority, category);
    taskManager.editTask(selection, editedTask);
    taskManager.saveTaskList();
    LoadTasks();
}

void GUI::OnDeleteTask(wxCommandEvent& event) {
    long selection = taskList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selection == wxNOT_FOUND) return;

    taskManager.deleteTask(selection);
    taskManager.saveTaskList();
    LoadTasks();
}

void GUI::OnSelectTask(wxCommandEvent& event) {
    long selection = taskList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selection == wxNOT_FOUND) return;

    Task selectedTask = taskManager.getSortedTasks()[selection];
    titleInput->SetValue(selectedTask.getTitle());
    descriptionInput->SetValue(selectedTask.getDescription());
    
    wxDateTime date;
    wxString dateString = selectedTask.getDueDate();
    date.ParseFormat(dateString, "%d.%m.%Y");
    dueDateInput->SetValue(date);

    priorityInput->SetValue(selectedTask.getPriority());
    categoryChoice->SetStringSelection(selectedTask.getCategory());
}