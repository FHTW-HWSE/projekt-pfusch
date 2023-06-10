#include "UiFascade.hpp"
#include "Enviroment.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <ios>

namespace Fascades
{         
    auto UiFascade::showMenu(UiMenu::MenuBase &menu) noexcept -> cpp::result<bool, std::string>
    {
        auto interaction = Enviroment::Config::instance()->get_interaction();

        return interaction->showMenu(menu);
    }

    auto UiFascade::get_int() noexcept -> cpp::result<int, std::string>
    {
        auto interaction = Enviroment::Config::instance()->get_interaction();

        return interaction->get_int();
    }

    auto UiFascade::write_string(const std::string &str) noexcept -> cpp::result<bool, std::string>
    {
        auto interaction = Enviroment::Config::instance()->get_interaction();

        return interaction->write_string(str);
    }

    auto UiFascade::print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string>
    {
        auto interaction = Enviroment::Config::instance()->get_interaction();

        return interaction->print_options_and_get_result(options);
    }

    auto UiFascade::print_options_and_get_result(std::vector<std::string> &options, std::string &leading_prompt) noexcept -> cpp::result<int, std::string>
    {

        auto interaction = Enviroment::Config::instance()->get_interaction();

        auto write_r = interaction->write_string(leading_prompt);

        if(write_r.has_error())
        {
            return cpp::fail(write_r.error());
        }

        return interaction->print_options_and_get_result(options);
    }
}