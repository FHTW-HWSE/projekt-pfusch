#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace Fascades
{
    class UiFascade
    {
        public:
            static auto showMenu(UiMenu::MenuBase &menu) noexcept -> cpp::result<bool, std::string>;
            static auto get_int() noexcept -> cpp::result<int, std::string>;
            static auto write_string(const std::string &str) noexcept -> cpp::result<void, std::string>;
            static auto print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string>;
            static auto print_options_and_get_result(std::vector<std::string> &options, std::string &leading_prompt) noexcept -> cpp::result<int, std::string>;
    };
}