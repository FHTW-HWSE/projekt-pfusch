#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace Interaction
{
    class InteractionBase
    {
        public:
            virtual ~InteractionBase(){};
            virtual void showMenu(UiMenu::MenuBase &menu) = 0;
            virtual auto get_int() noexcept -> cpp::result<int, std::string> = 0;
            virtual void print_string(const std::string &str) = 0;
            virtual auto print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string> = 0;
            virtual auto get_string() noexcept -> cpp::result<std::string, std::string> = 0;
    };
}