#include "UiFascade.hpp"
#include "Enviroment.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <ios>
#include <regex>

namespace Fascades
{         
    void UiFascade::showMenu(UiMenu::MenuBase &menu)
    {
        auto interaction = Enviroment::Config::instance()->get_interaction();

        interaction->showMenu(menu);
    
        return;
    }

    auto UiFascade::get_int() noexcept -> cpp::result<int, std::string>
    {
        auto interaction = Enviroment::Config::instance()->get_interaction();

        return interaction->get_int();
    }

    void UiFascade::print_string(const std::string &str)
    {
        auto interaction = Enviroment::Config::instance()->get_interaction();

        interaction->print_string(str);
    
        return;
    }

    auto UiFascade::print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string>
    {
        auto interaction = Enviroment::Config::instance()->get_interaction();

        return interaction->print_options_and_get_result(options);
    }

    auto UiFascade::print_options_and_get_result(std::vector<std::string> &options, const std::string &leading_prompt) noexcept -> cpp::result<int, std::string>
    {

        auto interaction = Enviroment::Config::instance()->get_interaction();

        interaction->print_string(leading_prompt);

        return interaction->print_options_and_get_result(options);
    }

    auto UiFascade::get_email() noexcept -> cpp::result<std::string, std::string>
    {
        auto interaction = Enviroment::Config::instance()->get_interaction();

        auto r_str = interaction->get_string();

        if(r_str.has_error())
        {
            return cpp::fail(r_str.error());
        }

        //https://stackoverflow.com/questions/14913341/how-do-i-check-a-user-input-string-with-email-format
        std::regex email_regex
        (
            "^[_a-z0-9-]+(.[_a-z0-9-]+)*@[a-z0-9-]+(.[a-z0-9-]+)*(.[a-z]{2,4})$"
            , std::regex_constants::ECMAScript | std::regex_constants::icase
        );

        bool is_emial = std::regex_search(r_str.value(), email_regex);

        if(!is_emial)
        {
            return cpp::fail("input is not an email address");
        }

        return r_str.value();
    }

    auto UiFascade::get_string() noexcept -> cpp::result<std::string, std::string>
    {
        auto interaction = Enviroment::Config::instance()->get_interaction();

        auto r_str = interaction->get_string();

        if(r_str.has_error())
        {
            return cpp::fail(r_str.error());
        }

        return r_str.value();
    }

}