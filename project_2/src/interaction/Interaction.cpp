#include "Interaction.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <ios>

namespace Interaction
{
    Interaction::Interaction()
    {

    }

    auto Interaction::showMenu(UiMenu::MenuBase &menu) noexcept -> cpp::result<bool, std::string>
    {
        menu.show();

        return true;
    }

    auto Interaction::get_int() noexcept -> cpp::result<int, std::string>
    {
        int num;

        std::cin >> num;

        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            return cpp::fail("Nan");
        }

        return num;
    }

    auto Interaction::write_string(const std::string &str) noexcept -> cpp::result<bool, std::string>
    {
        std::cout << str << std::endl;

        //throw exception;

        return true;
    }

    auto Interaction::print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string>
    {
        int i = 1;
        for (const std::string &opt : options)
        {
			std::string option = std::to_string(i++) + ": " + opt;

            auto write_r = write_string(option);

            if(write_r.has_error())
            {
                return cpp::fail(write_r.error());
            }
        }

        auto int_r = get_int();

        if(int_r.has_error())
        {
            return cpp::fail(int_r.error());
        }

        if(int_r.value() < 1 || int_r.value() > options.size())
        {
            return cpp::fail("invalid option chosen.");
        }

        return int_r.value();
    }
}