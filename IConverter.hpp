#pragma once
#include <string>

class IConverter {
public:
    virtual void convert(const std::string&) = 0;
};
