#pragma once
#include <wx/wx.h>

class Frame : public wxFrame {
public:
    Frame();

    wxButton* button1 {nullptr};
    wxTextCtrl* text1 {nullptr};
    wxListBox* listBox1 {nullptr};

    void OnButtonClicked(wxCommandEvent& evt);
};
