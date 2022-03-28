#include "Frame.hpp"
#include <wx/wx.h>

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "Hello World", wxPoint(30, 30), wxSize(800, 600)) {
    button1 = new wxButton(this, 10001, "Click Me", wxPoint(10, 10), wxSize(150, 50));
    text1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
    listBox1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
    Bind(wxEVT_BUTTON, &Frame::OnButtonClicked, this, 10001);
}

void Frame::OnButtonClicked(wxCommandEvent& evt) {
    listBox1->AppendString(text1->GetValue());
    evt.Skip();
}
