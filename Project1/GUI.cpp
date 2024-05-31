#include "GUI.h"

enum {
    ID_AddTask = 1,
    ID_EditTask,
    ID_DeleteTask
};

GUI::GUI(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)) {
    wxPanel* panel = new wxPanel(this, -1);

    taskList = new wxListBox(panel, wxID_ANY, wxPoint(10, 10), wxSize(200, 300));

    wxStaticText* titleLabel = new wxStaticText(panel, wxID_ANY, wxT("Title:"), wxPoint(220, 10));
    titleInput = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxPoint(300, 10), wxSize(250, 25));

    wxStaticText* descriptionLabel = new wxStaticText(panel, wxID_ANY, wxT("Description:"), wxPoint(220, 50));
    descriptionInput = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxPoint(300, 50), wxSize(250, 25));

    wxStaticText* dueDateLabel = new wxStaticText(panel, wxID_ANY, wxT("Due Date:"), wxPoint(220, 90));
    dueDateInput = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxPoint(300, 90), wxSize(250, 25));

    wxTextValidator validator(wxFILTER_NUMERIC);
    wxStaticText* priorityLabel = new wxStaticText(panel, wxID_ANY, wxT("Priority:"), wxPoint(220, 130));
    priorityInput = new wxTextCtrl(panel, wxID_ANY, wxT("0"), wxPoint(300, 130), wxSize(250, 25), 0, validator);

    wxStaticText* categoryLabel = new wxStaticText(panel, wxID_ANY, wxT("Category:"), wxPoint(220, 170));
    categoryInput = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxPoint(300, 170), wxSize(250, 25));

    wxButton* addButton = new wxButton(panel, ID_AddTask, wxT("Add Task"), wxPoint(220, 210));
    wxButton* editButton = new wxButton(panel, ID_EditTask, wxT("Edit Task"), wxPoint(320, 210));
    wxButton* deleteButton = new wxButton(panel, ID_DeleteTask, wxT("Delete Task"), wxPoint(420, 210));

    Connect(ID_AddTask, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnAddTask));
    Connect(ID_EditTask, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnEditTask));
    Connect(ID_DeleteTask, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnDeleteTask));
    Connect(wxID_ANY, wxEVT_LISTBOX, wxCommandEventHandler(GUI::OnSelectTask));
}

void GUI::OnAddTask(wxCommandEvent& event) {
    std::string title = titleInput->GetValue().ToStdString();
    std::string description = descriptionInput->GetValue().ToStdString();
    std::string dueDate = dueDateInput->GetValue().ToStdString();
    std::string priority = priorityInput->GetValue().ToStdString();
    std::string category = categoryInput->GetValue().ToStdString();

    Task newTask(title, description, dueDate, priority, category);
    taskManager.addTask(newTask);

    taskList->AppendString(title);
}

void GUI::OnEditTask(wxCommandEvent& event) {
    int selection = taskList->GetSelection();
    if (selection == wxNOT_FOUND) return;

    std::string title = titleInput->GetValue().ToStdString();
    std::string description = descriptionInput->GetValue().ToStdString();
    std::string dueDate = dueDateInput->GetValue().ToStdString();
    std::string priority = priorityInput->GetValue().ToStdString();
    std::string category = categoryInput->GetValue().ToStdString();

    Task editedTask(title, description, dueDate, priority, category);
    taskManager.editTask(selection, editedTask);

    taskList->SetString(selection, title);
}

void GUI::OnDeleteTask(wxCommandEvent& event) {
    int selection = taskList->GetSelection();
    if (selection == wxNOT_FOUND) return;

    taskManager.deleteTask(selection);
    taskList->Delete(selection);
}

void GUI::OnSelectTask(wxCommandEvent& event) {
    int selection = taskList->GetSelection();
    if (selection == wxNOT_FOUND) return;

    Task selectedTask = taskManager.getTasks()[selection];
    titleInput->SetValue(selectedTask.getTitle());
    descriptionInput->SetValue(selectedTask.getDescription());
    dueDateInput->SetValue(selectedTask.getDueDate());
    priorityInput->SetValue(selectedTask.getPriority());
    categoryInput->SetValue(selectedTask.getCategory());
}