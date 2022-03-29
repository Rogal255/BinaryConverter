#pragma once
#include <wx/wx.h>

constexpr uint8_t numberOfButtons_ {16};

enum myID {
    IDRadioButton_Dec = wxID_LAST + 1,
    IDRadioButton_Bin,
    IDRadioButton_Hex,
    IDButton_Clear,
    IDButton_0,
    IDListResult = IDButton_0 + numberOfButtons_,
};
