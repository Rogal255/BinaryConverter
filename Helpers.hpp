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
