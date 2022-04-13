#pragma once

#include <array>
#include <string>

class IReceiver;

class Converter {
public:
    Converter() = default;
    explicit Converter(IReceiver* frontend);
    void setFrontend(IReceiver* frontend);

    void convert(const std::string& input);

private:
    static std::string decToBase(const std::string& input, uint8_t base);
    static std::string baseToDec(const std::string& input, uint8_t base);
    IReceiver* frontend_ {nullptr};

    constexpr static bool baseValidator(uint8_t base);
    constexpr static std::array<const char, 16>
        hexMap {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    constexpr static uint8_t binBase {2};
    constexpr static uint8_t hexBase {16};
    static bool inputDecValidator(const std::string& input);
    static bool inputBinValidator(const std::string& input);
    static bool inputHexValidator(const std::string& input);
};
