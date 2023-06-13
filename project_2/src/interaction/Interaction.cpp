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

    void Interaction::showMenu(UiMenu::MenuBase &menu)
    {
        menu.show();

        return;
    }

    void Interaction::flush_cin()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    auto Interaction::get_int() noexcept -> cpp::result<int, std::string>
    {
        int num;

        std::cin >> num;

        flush_cin();

        if(std::cin.fail())
        {
            return cpp::fail("input was not an integer.");
        }

        return num;
    }

    void Interaction::print_string(const std::string &str)
    {
        std::cout << str << std::endl;

        if(std::cout.fail())
        {
            std::cerr << "Error while writing to stdout.";
        }

        return;
    }

    auto Interaction::print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string>
    {
        int i = 1;
        for (const std::string &opt : options)
        {
			std::string option = std::to_string(i++) + ": " + opt;

            print_string(option);
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

        return int_r.value() - 1;
    }

    auto Interaction::get_string() noexcept -> cpp::result<std::string, std::string>
    {
        std::string str;

        std::cin >> str;

        flush_cin();

        if(std::cin.fail())
        {
            return cpp::fail("could not get string from user");
        }

        return str;
    }

}