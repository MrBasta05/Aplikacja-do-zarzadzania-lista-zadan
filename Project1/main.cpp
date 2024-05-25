#include <wx/wx.h>
#include "GUI.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
    GUI* gui = new GUI(wxT("Task Manager"));
    gui->Show(true);

    return true;
}