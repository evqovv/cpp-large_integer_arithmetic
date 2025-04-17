#pragma once

#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

namespace evqovv {
namespace large_integer_arithmetic {
inline auto subtract(std::string_view a, std::string_view b) -> std::string;

namespace detail {
inline auto trim_leading_zeros(std::string_view number) -> std::string {
    auto const pos = number.find_first_not_of('0');
    if (pos == std::string_view::npos) {
        return "0";
    }
    number.remove_prefix(pos);
    return std::string(number);
}

inline auto skip_plus_signs(std::string_view &number) noexcept -> void {
    if (number[0] == '+') {
        number.remove_prefix(1);
    }
}

inline auto validate(std::string_view number) -> void {
    if (number.empty()) {
        throw std::invalid_argument("Number is empty");
    }

    if (number[0] == '+' || number[0] == '-') {
        number.remove_prefix(1);
    }

    if (number.empty()) {
        throw std::invalid_argument("Number has sign but no digits");
    }

    if (number.size() > 1 && number[0] == '0') {
        throw std::invalid_argument("Number has invalid leading zero");
    }

    for (auto &&c : number) {
        if (c < '0' || c > '9') {
            throw std::invalid_argument("Number contains non-digit character");
        }
    }
}

inline auto is_great_than_or_equal_to(std::string_view a,
                                      std::string_view b) noexcept -> bool {
    if (a.size() != b.size()) {
        return a.size() > b.size();
    } else {
        for (decltype(a.size()) i = 0; i != a.size(); ++i) {
            if (a[i] != b[i]) {
                return a[i] > b[i];
            }
        }

        return true;
    }
}

inline auto is_less_than(std::string_view a, std::string_view b) noexcept
    -> bool {
    return !is_great_than_or_equal_to(a, b);
}

inline auto multiply_single_digit(std::string_view number, int factor)
    -> std::string {
    std::string result;

    int carry = 0;
    for (auto it = number.crbegin(); it != number.crend(); ++it) {
        int digit = *it - '0';
        int product = digit * factor + carry;
        result.push_back(product % 10 + '0');
        carry = product / 10;
    }

    if (carry > 0) {
        result.push_back(carry + '0');
    }

    std::reverse(result.begin(), result.end());

    return result;
}

inline auto find_best_multiplier(std::string_view cur_dividend,
                                 std::string_view divisor)
    -> std::pair<int, std::string> {
    int low = 1;
    int high = 9;
    int best_quotient = 0;
    std::string best_product;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        auto temp = multiply_single_digit(divisor, mid);
        if (is_great_than_or_equal_to(cur_dividend, temp)) {
            best_quotient = mid;
            best_product = std::move(temp);
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return {best_quotient, best_product};
}

inline auto unsigned_divide(std::string_view a, std::string_view b)
    -> std::pair<std::string, std::string> {
    if (is_less_than(a, b)) {
        return {"0", std::string(a)};
    }

    std::string cur_dividend;
    std::string quotient;

    auto it = a.cbegin();
    while (it != a.cend()) {
        cur_dividend.push_back(*it++);

        if (is_less_than(cur_dividend, b)) {
            if (!quotient.empty()) {
                quotient.push_back('0');
            }
            continue;
        }

        auto [best_quotient, best_product] =
            find_best_multiplier(cur_dividend, std::string(b));
        quotient.push_back(best_quotient + '0');
        cur_dividend = subtract(cur_dividend, best_product);
    }

    std::string remainder = cur_dividend == "0" ? "0" : cur_dividend;

    return {quotient, remainder};
}
} // namespace detail

inline auto add(std::string_view a, std::string_view b) -> std::string {
    detail::validate(a);
    detail::validate(b);

    detail::skip_plus_signs(a);
    detail::skip_plus_signs(b);

    if (a[0] == '-' && b[0] != '-') {
        a.remove_prefix(1);
        return subtract(b, a);
    }

    if (a[0] != '-' && b[0] == '-') {
        b.remove_prefix(1);
        return subtract(a, b);
    }

    if (a[0] == '-' && b[0] == '-') {
        a.remove_prefix(1);
        b.remove_prefix(1);
        return "-" + add(a, b);
    }

    std::string result;
    result.reserve(std::max(a.size(), b.size()) + 1);

    int carry = 0;
    auto pos1 = a.crbegin();
    auto pos2 = b.crbegin();
    while (pos1 != a.crend() || pos2 != b.crend() || carry > 0) {
        int digit1 = pos1 != a.crend() ? *pos1++ - '0' : 0;
        int digit2 = pos2 != b.crend() ? *pos2++ - '0' : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }

    std::reverse(result.begin(), result.end());

    return result;
}

inline auto subtract(std::string_view a, std::string_view b) -> std::string {
    detail::validate(a);
    detail::validate(b);

    detail::skip_plus_signs(a);
    detail::skip_plus_signs(b);

    if (a == b) {
        return "0";
    }

    if (a[0] == '-' && b[0] != '-') {
        a.remove_prefix(1);
        return "-" + add(a, b);
    }

    if (a[0] != '-' && b[0] == '-') {
        b.remove_prefix(1);
        return add(a, b);
    }

    if (a[0] == '-' && b[0] == '-') {
        a.remove_prefix(1);
        b.remove_prefix(1);
        std::swap(a, b);
    }

    bool is_negative = false;
    if (detail::is_less_than(a, b)) {
        is_negative = true;
        std::swap(a, b);
    }

    std::string result;

    int borrow = 0;
    auto pos1 = a.crbegin();
    auto pos2 = b.crbegin();
    while (pos1 != a.crend() || pos2 != b.crend()) {
        int digit1 = pos1 != a.crend() ? *pos1++ - '0' : 0;
        int digit2 = pos2 != b.crend() ? *pos2++ - '0' : 0;

        digit1 -= borrow;
        borrow = 0;

        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        }

        result.push_back(digit1 - digit2 + '0');
    }

    std::reverse(result.begin(), result.end());

    return is_negative ? "-" + detail::trim_leading_zeros(result)
                       : detail::trim_leading_zeros(result);
}

inline auto multiply(std::string_view a, std::string_view b) -> std::string {
    detail::validate(a);
    detail::validate(b);

    detail::skip_plus_signs(a);
    detail::skip_plus_signs(b);

    if (a == "0" || a == "-0" || b == "0" || b == "-0") {
        return "0";
    }

    bool is_negative = false;
    if (a[0] == '-' && b[0] != '-') {
        a.remove_prefix(1);
        is_negative = true;
    }
    if (a[0] != '-' && b[0] == '-') {
        b.remove_prefix(1);
        is_negative = !is_negative;
    }
    if (a[0] == '-' && b[0] == '-') {
        a.remove_prefix(1);
        b.remove_prefix(1);
    }

    std::vector<int> temp(a.size() + b.size(), 0);
    for (auto it1 = a.crbegin(); it1 != a.crend(); ++it1) {
        int digit1 = *it1 - '0';
        auto i = a.size() - (it1 - a.crbegin());

        for (auto it2 = b.crbegin(); it2 != b.crend(); ++it2) {
            int digit2 = *it2 - '0';
            int product = digit1 * digit2;

            auto j = b.size() - (it2 - b.crbegin());

            int low = i + j - 2;
            int high = i + j - 1;

            int sum = product + temp[high];
            temp[high] = sum % 10;
            temp[low] += sum / 10;
        }
    }

    for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
        if (*it >= 10) {
            std::next(it) += *it / 10;
            *it %= 10;
        }
    }

    std::string result;
    std::transform(temp.begin(), temp.end(), std::back_inserter(result),
                   [](auto &&x) { return '0' + x; });

    return is_negative ? "-" + detail::trim_leading_zeros(result)
                       : detail::trim_leading_zeros(result);
}

inline auto divide(std::string_view a, std::string_view b)
    -> std::pair<std::string, std::string> {
    detail::validate(a);
    detail::validate(b);

    detail::skip_plus_signs(a);
    detail::skip_plus_signs(b);

    if (b == "0" || b == "-0") {
        throw std::invalid_argument("Division by zero");
    }

    bool dividend_negative = a[0] == '-';
    bool divisor_negative = b[0] == '-';
    auto dividend_abs = dividend_negative ? a.substr(1) : a;
    auto divisor_abs = divisor_negative ? b.substr(1) : b;

    if (dividend_abs == "0") {
        return {"0", "0"};
    }

    auto [qutoient_abs, remainder_abs] =
        detail::unsigned_divide(dividend_abs, divisor_abs);

    if (dividend_negative && remainder_abs != "0") {
        qutoient_abs = add(qutoient_abs, "1");
        remainder_abs = subtract(divisor_abs, remainder_abs);
    }

    bool quotient_negative = (dividend_negative != divisor_negative);
    std::string quotient = qutoient_abs;
    if (quotient_negative && qutoient_abs != "0") {
        quotient.insert(0, "-");
    }

    return {quotient, remainder_abs};
}
} // namespace large_integer_arithmetic
} // namespace evqovv
