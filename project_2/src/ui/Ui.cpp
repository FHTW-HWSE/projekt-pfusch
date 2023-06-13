
#include <iostream>
#include <stdlib.h>

#include "result.hpp"

auto get_int_from_user() noexcept -> cpp::result<int, std::string>
{
    int out = 0;

    std::cin >> out;

    return out;
}


auto get_string_from_stdin() noexcept -> cpp::result<std::string, std::string>
{
    return "";
}