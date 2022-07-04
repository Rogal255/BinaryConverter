#pragma once
#include <wx/wx.h>
#include <numeric>

constexpr char decPrefix[] {""};
constexpr char binPrefix[] {"0b"};
constexpr char hexPrefix[] {"0x"};
constexpr uint64_t uint64_MAX {std::numeric_limits<uint64_t>::max()};

namespace myFunc {
consteval uint8_t strlen(const char* str) {
    uint8_t counter {0};
    while (*str != '\0') {
        ++counter;
        ++str;
    }
    return counter;
}
};

enum myID {
    IDRadioButton_Dec = wxID_LAST + 1,
    IDRadioButton_Bin,
    IDRadioButton_Hex,
    IDButton_Clear,
    IDButton_Save,
    IDButton_0,
    IDButton_1,
    IDButton_2,
    IDButton_3,
    IDButton_4,
    IDButton_5,
    IDButton_6,
    IDButton_7,
    IDButton_8,
    IDButton_9,
    IDButton_A,
    IDButton_B,
    IDButton_C,
    IDButton_D,
    IDButton_E,
    IDButton_F,
    IDListResult,
};
