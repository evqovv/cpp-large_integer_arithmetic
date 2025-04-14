#include <gtest/gtest.h>
#include "large_integer_arithmetic.hpp"

using namespace evqovv::large_integer_arithmetic;

TEST(large_integer_arithmetic_test, add) {
    EXPECT_EQ(add("123", "456"), "579");
    EXPECT_EQ(add("123", "-456"), "-333");
    EXPECT_EQ(add("-123", "-456"), "-579");
    EXPECT_EQ(add("0", "0"), "0");
    EXPECT_EQ(add("-123", "123"), "0");
    EXPECT_EQ(add("-123", "+0"), "-123");
    EXPECT_EQ(add("-123", "-0"), "-123");
    EXPECT_EQ(add("-123", "0"), "-123");
    EXPECT_EQ(add("999", "+1"), "1000");
}

TEST(large_integer_arithmetic_test, subtract) {
    EXPECT_EQ(subtract("456", "123"), "333");
    EXPECT_EQ(subtract("123", "456"), "-333");
    EXPECT_EQ(subtract("-123", "456"), "-579");
    EXPECT_EQ(subtract("123", "-456"), "579");
    EXPECT_EQ(subtract("0", "0"), "0");
    EXPECT_EQ(subtract("-123", "+0"), "-123");
    EXPECT_EQ(subtract("-123", "-0"), "-123");
    EXPECT_EQ(subtract("-123", "0"), "-123");
}

TEST(large_integer_arithmetic_test, multiply) {
    EXPECT_EQ(multiply("123", "456"), "56088");
    EXPECT_EQ(multiply("123", "-456"), "-56088");
    EXPECT_EQ(multiply("-123", "-456"), "56088");
    EXPECT_EQ(multiply("0", "456"), "0");
    EXPECT_EQ(multiply("-0", "+0"), "0");
    EXPECT_EQ(multiply("+0", "123"), "0");
    EXPECT_EQ(multiply("-123", "-0"), "0");
}

TEST(large_integer_arithmetic_test, divide) {
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

TEST(large_integer_arithmetic_test, division_by_zero) {
    EXPECT_THROW(divide("123", "0"), std::invalid_argument);
    EXPECT_THROW(divide("123", "+0"), std::invalid_argument);
    EXPECT_THROW(divide("123", "-0"), std::invalid_argument);
}

TEST(large_integer_arithmetic_test, invalid_number) {
    EXPECT_THROW(add("0123", "0"), std::invalid_argument);
    EXPECT_THROW(add("1f23", "+0"), std::invalid_argument);
    EXPECT_THROW(add("+0123", "-0"), std::invalid_argument);
    EXPECT_THROW(add("+", "-0"), std::invalid_argument);
    EXPECT_THROW(subtract("0123", "0"), std::invalid_argument);
    EXPECT_THROW(subtract("1f23", "+0"), std::invalid_argument);
    EXPECT_THROW(subtract("+0123", "-0"), std::invalid_argument);
    EXPECT_THROW(subtract("+", "-0"), std::invalid_argument);
    EXPECT_THROW(multiply("0123", "0"), std::invalid_argument);
    EXPECT_THROW(multiply("1f23", "+0"), std::invalid_argument);
    EXPECT_THROW(multiply("+0123", "-0"), std::invalid_argument);
    EXPECT_THROW(multiply("+", "-0"), std::invalid_argument);
    EXPECT_THROW(divide("0123", "0"), std::invalid_argument);
    EXPECT_THROW(divide("1f23", "+0"), std::invalid_argument);
    EXPECT_THROW(divide("+0123", "-0"), std::invalid_argument);
    EXPECT_THROW(divide("+", "-0"), std::invalid_argument);
}
