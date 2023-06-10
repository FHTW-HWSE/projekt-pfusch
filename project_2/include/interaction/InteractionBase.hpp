#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace Interaction
{
    class InteractionBase
    {
        public:
            virtual ~InteractionBase(){};
            virtual auto showMenu(UiMenu::MenuBase &menu) noexcept -> cpp::result<bool, std::string> = 0;
            virtual auto get_int() noexcept -> cpp::result<int, std::string> = 0;
            virtual auto write_string(const std::string &str) noexcept -> cpp::result<bool, std::string> = 0;
            virtual auto print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string> = 0;
    };
}