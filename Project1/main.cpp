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


//#include <wx/wx.h>
//
//class App : public wxApp {
//public:
//    bool OnInit() {
//        wxFrame* window = new wxFrame(NULL, wxID_ANY, "GUI Test", wxDefaultPosition, wxSize(690, 690));
//        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
//        wxPanel* panel = new wxPanel(this, -1);
//        taskList = new wxListBox(panel, wxID_ANY, wxPoint(10, 10), wxSize(200, 300));
//        taskList->AppendString("task");
//
//        wxStaticText* text = new wxStaticText(window, wxID_ANY, "FIUUUUUUUUUT",
//            wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
//        wxStaticText* text2 = new wxStaticText(window, wxID_ANY, "Dziekan skurwysyn robi mi loda",
//            wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
//        text->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
//        sizer->Add(text, 1, wxALIGN_CENTER);
//        sizer->Add(text2, 1, wxALIGN_CENTER);
//        window->SetSizer(sizer);
//        window->Show();
//        return true;
//    }
//};
//
////heloooo
//wxIMPLEMENT_APP(App);