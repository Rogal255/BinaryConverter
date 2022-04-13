#include "Converter.hpp"
#include "Helpers.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>
#include "IReceiver.hpp"

Converter::Converter(IReceiver* frontend) : frontend_ {frontend} { }
void Converter::setFrontend(IReceiver* frontend) { frontend_ = frontend; }

void Converter::convert(const std::string& input) {
    if (inputHexValidator(input)) {
        std::string dec = baseToDec(input, hexBase);
        frontend_->setDec(dec);
        frontend_->setBin(decToBase(dec, binBase));
        return;
    }
    if (inputBinValidator(input)) {
        std::string dec = baseToDec(input, binBase);
        frontend_->setDec(dec);
        frontend_->setHex(decToBase(dec, hexBase));
        return;
    }
    if (inputDecValidator(input)) {
        frontend_->setBin(decToBase(input, binBase));
        frontend_->setHex(decToBase(input, hexBase));
        return;
    }
}

std::string Converter::decToBase(const std::string& input, const uint8_t base) {
    if (!Converter::baseValidator(base)) {
        throw std::invalid_argument("Converter::decToBase -> wrong base");
    }
    unsigned long long number {std::stoull(input.substr(myFunc::strlen(decPrefix)))};
    uint8_t reminder {0};
    std::string result;
    while (number > 0) {
        reminder = number % base;
        result.push_back(hexMap[reminder]);
        number /= base;
    }
    std::string prefix;
    if (base == binBase) {
        prefix = binPrefix;
    } else {
        prefix = hexPrefix;
    }
    std::reverse(prefix.begin(), prefix.end());
    result.append(prefix);
    std::reverse(result.begin(), result.end());
    return result;
}

std::string Converter::baseToDec(const std::string& input, const uint8_t base) {
    if (!baseValidator(base)) {
        throw std::invalid_argument("Converter::baseToDec -> wrong base");
    }
    std::string result;
    std::string rawInput;
    if (base == binBase) {
        rawInput = input.substr(myFunc::strlen(binPrefix));
        result = binPrefix;
    } else {
        rawInput = input.substr(myFunc::strlen(hexPrefix));
        result = hexPrefix;
    }
    std::size_t result_num {0};
    for (std::size_t i {0}; i < rawInput.size(); ++i) {
        uint8_t num = std::distance(hexMap.cbegin(), std::find(hexMap.cbegin(), hexMap.cend(), rawInput[i]));
        result_num += num * static_cast<std::size_t>(std::pow(base, rawInput.size() - 1 - i));
    }
    result.append(std::to_string(result_num));
    return result;
}

constexpr bool Converter::baseValidator(uint8_t base) { return base == binBase || base == hexBase; }

bool Converter::inputDecValidator(const std::string& input) {
    if constexpr (myFunc::strlen(decPrefix)) {
        if (input.substr(0, myFunc::strlen(decPrefix)) != decPrefix) {
            return false;
        }
    }
    if (!std::all_of(input.cbegin() + myFunc::strlen(decPrefix), input.cend(), ::isdigit)) {
        return false;
    }
    return true;
}

bool Converter::inputBinValidator(const std::string& input) {
    if (input.size() < myFunc::strlen(binPrefix)) {
        return false;
    }
    if (input.substr(0, myFunc::strlen(binPrefix)) != binPrefix) {
        return false;
    }
    if (!std::all_of(input.cbegin() + myFunc::strlen(binPrefix), input.cend(), [&](auto c) {
            return c == hexMap[0] || c == hexMap[1];
        })) {
        return false;
    }
    return true;
}

bool Converter::inputHexValidator(const std::string& input) {
    if (input.size() < myFunc::strlen(hexPrefix)) {
        return false;
    }
    if (input.substr(0, myFunc::strlen(hexPrefix)) != hexPrefix) {
        return false;
    }
    if (!std::all_of(input.cbegin() + myFunc::strlen(hexPrefix), input.cend(), [&](auto c) {
            return std::find(hexMap.cbegin(), hexMap.cend(), c) != hexMap.cend();
        })) {
        return false;
    }
    return true;
}
