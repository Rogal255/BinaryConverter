#include <string>

class IFrontend {
public:
    virtual ~IFrontend() = default;
    virtual void setDec(const std::string&) = 0;
    virtual void setBin(const std::string&) = 0;
    virtual void setHex(const std::string&) = 0;
};
