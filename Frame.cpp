#include "Frame.hpp"
#include <wx/listctrl.h>
#include <wx/wx.h>

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "Binary converter", wxPoint(30, 30), wxSize(400, 600)) {
    std::cout << "1\n";
    auto* controlSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer->Add(RButtonDec_, 1, wxEXPAND | wxALL, 10);
    controlSizer->Add(RButtonBin_, 1, wxEXPAND | wxALL, 10);
    controlSizer->Add(RButtonHex_, 1, wxEXPAND | wxALL, 10);
    controlSizer->Add(buttonClear_, 1, wxEXPAND | wxALL, 10);

    auto* buttonSizer = new wxGridSizer(4, 4, 0, 0);
    for (uint8_t button {0}; button < numberOfButtons_; ++button) {
        arrButtons_[button] = new wxButton(this, IDButton_0 + button, "0", wxDefaultPosition, wxSize(50, 50));
        buttonSizer->Add(arrButtons_[button], 1, wxEXPAND | wxALL, 10);
    }

    auto* resultsSizer = new wxBoxSizer(wxHORIZONTAL);
    resultsSizer->Add(listResult_, 1, wxEXPAND | wxALL, 10);

    auto* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(controlSizer, 0, wxEXPAND);
    mainSizer->Add(buttonSizer, 0, wxEXPAND);
    mainSizer->Add(resultsSizer, 1, wxEXPAND);
    this->SetSizerAndFit(mainSizer);
}
