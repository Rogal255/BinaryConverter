#include "Converter.hpp"
#include "Helpers.hpp"
#include "IReceiver.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <optional>
#include <string>

Converter::Converter(IReceiver* frontend) : frontend_ {frontend} { }
void Converter::setFrontend(IReceiver* frontend) { frontend_ = frontend; }

bool Converter::convert(const std::string& input) {
    if (inputHexValidator(input)) {
        std::optional<std::string> dec = baseToDec(input, hexBase);
        if (dec) {
            frontend_->setDec(*dec);
        } else {
            return false;
        }
        if (std::optional<std::string> bin = decToBase(*dec, binBase)) {
            frontend_->setBin(*bin);
        } else {
            return false;
        }
        return true;
    }
    if (inputBinValidator(input)) {
        std::optional<std::string> dec = baseToDec(input, binBase);
        if (dec) {
            frontend_->setDec(*dec);
        } else {
            return false;
        }
        if (std::optional<std::string> hex = decToBase(*dec, hexBase)) {
            frontend_->setHex(*hex);
        } else {
            return false;
        }
        return true;
    }
    if (inputDecValidator(input)) {
        if (std::optional<std::string> bin = decToBase(input, binBase)) {
            frontend_->setBin(*bin);
        } else {
            return false;
        }
        if (std::optional<std::string> hex = decToBase(input, hexBase)) {
            frontend_->setHex(*hex);
        } else {
            return false;
        }
        return true;
    }
    return false;
}

std::optional<std::string> Converter::decToBase(const std::string& input, const uint8_t base) {
    if (!Converter::baseValidator(base)) {
        return std::nullopt;
    }
    uint64_t number {0};
    try {
        number = std::stoull(input.substr(myFunc::strlen(decPrefix)));
    } catch (const std::out_of_range&) { return std::nullopt; }
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
    if (result.size() == prefix.size()) {
        result.append("0");
    }
    return result;
}

std::optional<std::string> Converter::baseToDec(const std::string& input, const uint8_t base) {
    if (!baseValidator(base)) {
        return std::nullopt;
    }
    std::string rawInput;
    if (base == binBase) {
        rawInput = input.substr(myFunc::strlen(binPrefix));
        if (rawInput.size() > static_cast<unsigned long>(std::log2(uint64_MAX))) {
            return std::nullopt;
        }
    } else {
        rawInput = input.substr(myFunc::strlen(hexPrefix));
        if (rawInput.size() > static_cast<unsigned long>(std::log2(uint64_MAX) / 4)) {
            return std::nullopt;
        }
    }
    uint64_t result {0};
    for (std::size_t i {0}; i < rawInput.size(); ++i) {
        uint64_t partialRes = std::distance(hexMap.cbegin(), std::find(hexMap.cbegin(), hexMap.cend(), rawInput[i]));
        partialRes *= static_cast<uint64_t>(std::pow(base, rawInput.size() - 1 - i));
        const uint64_t diff = uint64_MAX - partialRes;
        if (result > diff) {
            return std::nullopt;
        }
        result += partialRes;
    }
    return std::to_string(result);
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
