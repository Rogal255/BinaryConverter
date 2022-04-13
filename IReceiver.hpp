#include <string>

class IReceiver {
public:
    virtual ~IReceiver() = default;
    virtual void setDec(const std::string&) = 0;
    virtual void setBin(const std::string&) = 0;
    virtual void setHex(const std::string&) = 0;
};
