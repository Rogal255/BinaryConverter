#include "../Converter.hpp"
#include "DummyFrontend.hpp"
#include <gtest/gtest.h>

class ConverterUnitTests : public ::testing::Test {
protected:
    DummyFrontend frontend;
    Converter converter {&frontend};
};

TEST_F(ConverterUnitTests, decInput) {
    ASSERT_TRUE(true);
}
