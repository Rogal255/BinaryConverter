#pragma once
#include <string>

class IConverter {
public:
    virtual bool convert(const std::string&) = 0;
};
