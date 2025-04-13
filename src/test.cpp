#include <gtest/gtest.h>
#include "large_integer_arithmetic.hpp"

using namespace evqovv::large_integer_arithmetic;
TEST(LargeIntegerArithmeticTest, Add) {
    EXPECT_EQ(add("123", "456"), "579");
    EXPECT_EQ(add("123", "-456"), "-333");
    EXPECT_EQ(add("-123", "-456"), "-579");
    EXPECT_EQ(add("0", "0"), "0");
    EXPECT_EQ(add("-123", "123"), "0");
    EXPECT_EQ(add("-123", "+0"), "-123");
    EXPECT_EQ(add("-123", "-0"), "-123");
    EXPECT_EQ(add("-123", "0"), "-123");
}

TEST(LargeIntegerArithmeticTest, Subtract) {
    EXPECT_EQ(subtract("456", "123"), "333");
    EXPECT_EQ(subtract("123", "456"), "-333");
    EXPECT_EQ(subtract("-123", "456"), "-579");
    EXPECT_EQ(subtract("123", "-456"), "579");
    EXPECT_EQ(subtract("0", "0"), "0");
    EXPECT_EQ(subtract("-123", "+0"), "-123");
    EXPECT_EQ(subtract("-123", "-0"), "-123");
    EXPECT_EQ(subtract("-123", "0"), "-123");
}

TEST(LargeIntegerArithmeticTest, Multiply) {
    EXPECT_EQ(multiply("123", "456"), "56088");
    EXPECT_EQ(multiply("123", "-456"), "-56088");
    EXPECT_EQ(multiply("-123", "-456"), "56088");
    EXPECT_EQ(multiply("0", "456"), "0");
    EXPECT_EQ(multiply("-0", "+0"), "0");
    EXPECT_EQ(multiply("+0", "123"), "0");
    EXPECT_EQ(multiply("-123", "-0"), "0");
}

TEST(LargeIntegerArithmeticTest, Divide) {
    auto ret = divide("123", "456");
    EXPECT_EQ(ret.first, "0");
    EXPECT_EQ(ret.second, "123");

    ret = divide("-123", "456");
    EXPECT_EQ(ret.first, "-1");
    EXPECT_EQ(ret.second, "333");

    ret = divide("1234", "100");
    EXPECT_EQ(ret.first, "12");
    EXPECT_EQ(ret.second, "34");

    ret = divide("1234", "100");
    EXPECT_EQ(ret.first, "12");
    EXPECT_EQ(ret.second, "34");

    ret = divide("0", "100");
    EXPECT_EQ(ret.first, "0");
    EXPECT_EQ(ret.second, "0");

    ret = divide("+0", "100");
    EXPECT_EQ(ret.first, "0");
    EXPECT_EQ(ret.second, "0");

    ret = divide("-0", "100");
    EXPECT_EQ(ret.first, "0");
    EXPECT_EQ(ret.second, "0");
}

TEST(LargeIntegerArithmeticTest, DivisionByZero) {
    EXPECT_THROW(divide("123", "0"), std::invalid_argument);
    EXPECT_THROW(divide("123", "+0"), std::invalid_argument);
    EXPECT_THROW(divide("123", "-0"), std::invalid_argument);
}
