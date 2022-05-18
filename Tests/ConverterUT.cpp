#include "../Converter.hpp"
#include "DummyFrontend.hpp"
#include <array>
#include <gtest/gtest.h>

class ConverterUnitTests : public ::testing::Test {
protected:
    DummyFrontend frontend;
    Converter converter {&frontend};
    std::array<std::array<std::string, 3>, 8> data {
        {{"456", "0b111001000", "0x1C8"},
         {"0", "0b0", "0x0"},
         {"1", "0b1", "0x1"},
         {"2", "0b10", "0x2"},
         {"255", "0b11111111", "0xFF"},
         {"2000000000", "0b1110111001101011001010000000000", "0x77359400"},
         {"4294967295", "0b11111111111111111111111111111111", "0xFFFFFFFF"},
         {"18446744073709551615",
          "0b1111111111111111111111111111111111111111111111111111111111111111",
          "0xFFFFFFFFFFFFFFFF"}}};
};

TEST_F(ConverterUnitTests, decInput) {
    for (const auto& arr : data) {
        converter.convert(arr[0]);
        ASSERT_EQ(frontend.resultBin, arr[1]);
        ASSERT_EQ(frontend.resultHex, arr[2]);
    }
}

TEST_F(ConverterUnitTests, binInput) {
    for (const auto& arr : data) {
        converter.convert(arr[1]);
        ASSERT_EQ(frontend.resultDec, arr[0]);
        ASSERT_EQ(frontend.resultHex, arr[2]);
    }
}

TEST_F(ConverterUnitTests, hexInput) {
    for (const auto& arr : data) {
        converter.convert(arr[2]);
        ASSERT_EQ(frontend.resultDec, arr[0]);
        ASSERT_EQ(frontend.resultBin, arr[1]);
    }
}

TEST(ConverterOverflowTest, tooBigInput) {
    DummyFrontend frontend;
    Converter converter {&frontend};
    std::array<std::array<std::string, 3>, 1> data {
        {{"18446744073709551616",
          "0b10000000000000000000000000000000000000000000000000000000000000000",
          "0x10000000000000000"}}};
    for (unsigned long i {0}; i < data.size(); ++i) {
        for (uint8_t input {0}; input < static_cast<uint8_t>(data[i].size()); ++input) {
            EXPECT_FALSE(converter.convert(data[i][input]));
        }
    }
}
