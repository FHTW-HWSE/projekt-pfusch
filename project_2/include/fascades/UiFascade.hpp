#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace Fascades
{
    class UiFascade
    {
        public:
            static void showMenu(UiMenu::MenuBase &menu);
            static auto get_int() noexcept -> cpp::result<int, std::string>;
            static void print_string(const std::string &str);
            static auto print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string>;
            static auto print_options_and_get_result(std::vector<std::string> &options, const std::string &leading_prompt) noexcept -> cpp::result<int, std::string>;
            static auto get_email() noexcept -> cpp::result<std::string, std::string>;
            static auto get_string() noexcept -> cpp::result<std::string, std::string>;

    };
}