#include "../IFrontend.hpp"
#include <string>

class DummyFrontend : public IFrontend {
public:
    ~DummyFrontend() override = default;
    void setDec(const std::string& dec) override { resultDec = dec; }
    void setBin(const std::string& bin) override { resultBin = bin; }
    void setHex(const std::string& hex) override { resultHex = hex; }
    std::string resultDec;
    std::string resultBin;
    std::string resultHex;
};
