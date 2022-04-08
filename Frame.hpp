#pragma once
#include "Helpers.hpp"
#include <array>
#include <wx/listctrl.h>
#include <wx/radiobut.h>
#include <wx/wx.h>

class Frame : public wxFrame {
public:
    Frame();

private:
    void InitUI();
    wxStaticBoxSizer* resultBox_ = new wxStaticBoxSizer(wxHORIZONTAL, this, "Results");
    wxStaticText* resultLabel1_ {new wxStaticText(resultBox_->GetStaticBox(), wxID_ANY, "DEC")};
    wxStaticText* resultLabel2_ {new wxStaticText(resultBox_->GetStaticBox(), wxID_ANY, "HEX")};
    wxTextCtrl* result1_ {new wxTextCtrl(resultBox_->GetStaticBox(), wxID_ANY)};
    wxTextCtrl* result2_ {new wxTextCtrl(resultBox_->GetStaticBox(), wxID_ANY)};

    wxStaticBoxSizer* baseSelectionBox_ = new wxStaticBoxSizer(wxHORIZONTAL, this, "Input base");
    wxRadioButton* RButtonDec_ {new wxRadioButton(baseSelectionBox_->GetStaticBox(), IDRadioButton_Dec, "Dec")};
    wxRadioButton* RButtonBin_ {new wxRadioButton(baseSelectionBox_->GetStaticBox(), IDRadioButton_Bin, "Bin")};
    wxRadioButton* RButtonHex_ {new wxRadioButton(baseSelectionBox_->GetStaticBox(), IDRadioButton_Hex, "Hex")};

    wxButton* buttonSave_ {new wxButton(this, wxID_ANY, "Save")};
    wxButton* buttonClear_ {new wxButton(this, IDButton_Clear, "Clear")};

    wxButton* button0_ {new wxButton(this, IDButton_0, "0", wxDefaultPosition, wxSize(50, 50))};
    wxButton* button1_ {new wxButton(this, IDButton_1, "1", wxDefaultPosition, wxSize(50, 50))};
    wxButton* button2_ {new wxButton(this, IDButton_2, "2", wxDefaultPosition, wxSize(50, 50))};
    wxButton* button3_ {new wxButton(this, IDButton_3, "3", wxDefaultPosition, wxSize(50, 50))};
    wxButton* button4_ {new wxButton(this, IDButton_4, "4", wxDefaultPosition, wxSize(50, 50))};
    wxButton* button5_ {new wxButton(this, IDButton_5, "5", wxDefaultPosition, wxSize(50, 50))};
    wxButton* button6_ {new wxButton(this, IDButton_6, "6", wxDefaultPosition, wxSize(50, 50))};
    wxButton* button7_ {new wxButton(this, IDButton_7, "7", wxDefaultPosition, wxSize(50, 50))};
    wxButton* button8_ {new wxButton(this, IDButton_8, "8", wxDefaultPosition, wxSize(50, 50))};
    wxButton* button9_ {new wxButton(this, IDButton_9, "9", wxDefaultPosition, wxSize(50, 50))};
    wxButton* buttonA_ {new wxButton(this, IDButton_A, "A", wxDefaultPosition, wxSize(50, 50))};
    wxButton* buttonB_ {new wxButton(this, IDButton_B, "B", wxDefaultPosition, wxSize(50, 50))};
    wxButton* buttonC_ {new wxButton(this, IDButton_C, "C", wxDefaultPosition, wxSize(50, 50))};
    wxButton* buttonD_ {new wxButton(this, IDButton_D, "D", wxDefaultPosition, wxSize(50, 50))};
    wxButton* buttonE_ {new wxButton(this, IDButton_E, "E", wxDefaultPosition, wxSize(50, 50))};
    wxButton* buttonF_ {new wxButton(this, IDButton_F, "F", wxDefaultPosition, wxSize(50, 50))};

    wxListView* listResult_ {new wxListView(this, IDListResult)};
};
