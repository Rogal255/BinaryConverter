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
    wxRadioButton* RButtonDec_ {new wxRadioButton(this, IDRadioButton_Dec, "Dec")};
    wxRadioButton* RButtonBin_ {new wxRadioButton(this, IDRadioButton_Bin, "Bin")};
    wxRadioButton* RButtonHex_ {new wxRadioButton(this, IDRadioButton_Hex, "Hex")};
    wxButton* buttonClear_ {new wxButton(this, IDButton_Clear, "Clear")};
    wxListCtrl* listResult_ {new wxListCtrl(this, IDListResult)};
    std::array<wxButton*, numberOfButtons_> arrButtons_;
};
