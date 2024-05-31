#include "GUI.h"

enum {
    ID_AddTask = 1,
    ID_EditTask,
    ID_DeleteTask
};

GUI::GUI(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 400)) {
    wxPanel* panel = new wxPanel(this, -1);

    taskList = new wxListCtrl(panel, wxID_ANY, wxPoint(10, 10), wxSize(200, 300), wxLC_REPORT | wxLC_SINGLE_SEL);

    taskList->InsertColumn(0, wxT("Title"), wxLIST_FORMAT_LEFT, 150);
    taskList->InsertColumn(1, wxT("Category"), wxLIST_FORMAT_LEFT, 150);

    wxStaticText* titleLabel = new wxStaticText(panel, wxID_ANY, wxT("Title:"), wxPoint(420, 10));
    titleInput = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxPoint(500, 10), wxSize(250, 25));

    wxStaticText* descriptionLabel = new wxStaticText(panel, wxID_ANY, wxT("Description:"), wxPoint(420, 50));
    descriptionInput = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxPoint(500, 50), wxSize(250, 105), wxTE_MULTILINE);

    wxStaticText* dueDateLabel = new wxStaticText(panel, wxID_ANY, wxT("Due Date:"), wxPoint(420, 170));
    dueDateInput = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxPoint(500, 170), wxSize(250, 25));

    wxTextValidator validator(wxFILTER_NUMERIC);
    wxStaticText* priorityLabel = new wxStaticText(panel, wxID_ANY, wxT("Priority:"), wxPoint(420, 210));
    priorityInput = new wxTextCtrl(panel, wxID_ANY, wxT("0"), wxPoint(500, 210), wxSize(250, 25), 0, validator);


    wxStaticText* categoryLabel = new wxStaticText(panel, wxID_ANY, wxT("Category:"), wxPoint(500, 250));
    wxString categories[] = { wxT("Urgent"), wxT("Regular"), wxT("Low Priority") };
    categoryChoice = new wxChoice(panel, wxID_ANY, wxPoint(500, 250), wxSize(250, 25), WXSIZEOF(categories), categories);
    categoryChoice->SetSelection(0); // Default selection

    wxButton* addButton = new wxButton(panel, ID_AddTask, wxT("Add Task"), wxPoint(450, 290));
    wxButton* editButton = new wxButton(panel, ID_EditTask, wxT("Edit Task"), wxPoint(550, 290));
    wxButton* deleteButton = new wxButton(panel, ID_DeleteTask, wxT("Delete Task"), wxPoint(650, 290));

    Connect(ID_AddTask, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnAddTask));
    Connect(ID_EditTask, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnEditTask));
    Connect(ID_DeleteTask, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnDeleteTask));
    Connect(wxID_ANY, wxEVT_LIST_ITEM_SELECTED, wxCommandEventHandler(GUI::OnSelectTask));

    LoadTasks();
}

void GUI::LoadTasks() {
    taskList->DeleteAllItems();
    const auto& tasks = taskManager.getTasks();
    for (size_t i = 0; i < tasks.size(); ++i) {
        const auto& task = tasks[i];
        wxListItem item;
        item.SetId(i);
        item.SetText(task.getTitle());

        // Set custom background color for different categories
        if (task.getCategory() == "Urgent") {
            item.SetBackgroundColour(*wxRED);
        }
        else if (task.getCategory() == "Regular") {
            item.SetBackgroundColour(*wxGREEN);
        }
        else {
            item.SetBackgroundColour(*wxWHITE);
        }

        taskList->InsertItem(item);
        taskList->SetItem(i, 1, task.getCategory());
    }
}

void GUI::OnAddTask(wxCommandEvent& event) {
    std::string title = titleInput->GetValue().ToStdString();
    std::string description = descriptionInput->GetValue().ToStdString();
    std::string dueDate = dueDateInput->GetValue().ToStdString();
    std::string priority = priorityInput->GetValue().ToStdString();
    std::string category = categoryChoice->GetStringSelection().ToStdString();

    Task newTask(title, description, dueDate, priority, category);
    taskManager.addTask(newTask);

    LoadTasks();
}

void GUI::OnEditTask(wxCommandEvent& event) {
    long selection = taskList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selection == wxNOT_FOUND) return;

    std::string title = titleInput->GetValue().ToStdString();
    std::string description = descriptionInput->GetValue().ToStdString();
    std::string dueDate = dueDateInput->GetValue().ToStdString();
    std::string priority = priorityInput->GetValue().ToStdString();
    std::string category = categoryChoice->GetStringSelection().ToStdString();

    Task editedTask(title, description, dueDate, priority, category);
    taskManager.editTask(selection, editedTask);

    LoadTasks();
}

void GUI::OnDeleteTask(wxCommandEvent& event) {
    long selection = taskList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selection == wxNOT_FOUND) return;

    taskManager.deleteTask(selection);
    LoadTasks();
}

void GUI::OnSelectTask(wxCommandEvent& event) {
    long selection = taskList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selection == wxNOT_FOUND) return;

    Task selectedTask = taskManager.getTasks()[selection];
    titleInput->SetValue(selectedTask.getTitle());
    descriptionInput->SetValue(selectedTask.getDescription());
    dueDateInput->SetValue(selectedTask.getDueDate());
    priorityInput->SetValue(selectedTask.getPriority());
    categoryChoice->SetStringSelection(selectedTask.getCategory());
}