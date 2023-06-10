#pragma once

#include "Base.hpp"
#include "InteractionBase.hpp"

namespace Interaction
{
    class Interaction : public InteractionBase
    {
        public:
            Interaction();
            virtual ~Interaction(){};
            virtual auto showMenu(UiMenu::MenuBase &menu) noexcept -> cpp::result<bool, std::string> override;
            virtual auto get_int() noexcept -> cpp::result<int, std::string> override;
            virtual auto write_string(const std::string &str) noexcept -> cpp::result<bool, std::string> override;
            virtual auto print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string> override;
    };
}