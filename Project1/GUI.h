#pragma once
#ifndef GUI_H
#define GUI_H

#include <wx/wx.h>
#include <wx/valtext.h>
#include <wx/listctrl.h>
#include <wx/choice.h>
#include <wx/colour.h>
#include "TaskManager.h"
#include <wx/datectrl.h>

class GUI : public wxFrame {
private:
    TaskManager taskManager;

    // Elementy interfejsu
    wxListCtrl* taskList;
    wxTextCtrl* titleInput;
    wxTextCtrl* descriptionInput;
    wxDatePickerCtrl* dueDateInput;
    wxSpinCtrl* priorityInput;
    wxChoice* categoryChoice;

public:
    GUI(const wxString& title);

    // Metody obs�ugi zdarze�
    void OnAddTask(wxCommandEvent& event);
    void OnEditTask(wxCommandEvent& event);
    void OnDeleteTask(wxCommandEvent& event);
    void OnSelectTask(wxCommandEvent& event);
    void OnSaveTask(wxCommandEvent& event);
    void LoadTasks();
};

#endif // GUI_H