#pragma once
#ifndef GUI_H
#define GUI_H

#include <wx/wx.h>
#include <wx/valtext.h>
#include "TaskManager.h"

class GUI : public wxFrame {
private:
    TaskManager taskManager;

    // Elementy interfejsu
    wxListBox* taskList;
    wxTextCtrl* titleInput;
    wxTextCtrl* descriptionInput;
    wxTextCtrl* dueDateInput;
    wxTextCtrl* priorityInput;
    wxTextCtrl* categoryInput;

public:
    GUI(const wxString& title);

    // Metody obs³ugi zdarzeñ
    void OnAddTask(wxCommandEvent& event);
    void OnEditTask(wxCommandEvent& event);
    void OnDeleteTask(wxCommandEvent& event);
    void OnSelectTask(wxCommandEvent& event);
};

#endif // GUI_H