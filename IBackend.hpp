#pragma once
#include <string>

class IBackend {
public:
    virtual bool convert(const std::string&) = 0;
};
