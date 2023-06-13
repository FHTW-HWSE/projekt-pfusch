#pragma once

#include "Base.hpp"
#include "InteractionBase.hpp"

namespace Interaction
{
    class Interaction : public InteractionBase
    {
        private:
            static void flush_cin();
            
        public:
            Interaction();
            virtual ~Interaction(){};
            virtual void showMenu(UiMenu::MenuBase &menu) override;
            virtual auto get_int() noexcept -> cpp::result<int, std::string> override;
            virtual void print_string(const std::string &str) override;
            virtual auto print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string> override;
            virtual auto get_string() noexcept -> cpp::result<std::string, std::string>;
    };
}