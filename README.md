# Large integer arithmetic  

A lightweight C++ header-only library for performing basic arithmetic operations on arbitrary-length integers represented as strings.

## Features  
-  Handles arbitrarily large integers (limited only by memory)  
- Supports ``+``, ``-``, ``*``, and ``/``  
- Accepts numbers as ``std::string_view``  
- Strict validation of input format  
- No external dependencies, fully header-only  

## Usage  
### Dependency setting
```cpp
#include "large_integer_arithmetic.hpp"
```  

### API Reference  
``std::string add(std::string_view a, std::string_view b)`` performs addition of two signed integers.  

``std::string subtract(std::string_view a, std::string_view b)`` performs subtraction of two signed integers.  

``std::string multiply(std::string_view a, std::string_view b)`` performs multiplication of two signed integers.  

``std::pair<std::string, std::string> divide(std::string_view a, std::string_view b)`` performs division of two signed integers.

### Examples  
```cpp
using namespace evqovv::large_integer_arithmetic;

std::string a = "12345678901234567890";
std::string b = "98765432109876543210";
std::string c = "56789";

// 12345678901234567890 + 98765432109876543210 = 111111111011111111100
std::print("{} + {} = {}\n", a, b, add(a, b));

// 12345678901234567890 - 98765432109876543210 = -86419753208641975320
std::print("{} - {} = {}\n", a, b, subtract(a, b));

// 12345678901234567890 * 98765432109876543210 = 1219326311370217952237463801111263526900
std::print("{} * {} = {}\n", a, b, multiply(a, b));

auto ret = divide(a, c);
// 12345678901234567890 / 56789 = 217395603043451, 29051
std::print("{} / {} = {}, {}\n", a, c, ret.first, ret.second);
```