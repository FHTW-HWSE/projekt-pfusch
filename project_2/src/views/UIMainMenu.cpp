#include "Base.hpp"
#include "UIMainMenu.hpp"
#include "ConfigTablesMenu.hpp"
#include "UiFascade.hpp"
#include "DbFascade.hpp"

namespace UiMenu
{
    MainMenu::MainMenu()
    {

    }

    MainMenu::~MainMenu()
    {

    }

    void MainMenu::show()
    {
        auto intro_msg = Fascades::UiFascade::write_string("Welcome to our awesome pfusch.");

        bool repeat = true;

        while (repeat)
        {
            std::vector<std::string> options;
            options.push_back("configure table layout");
            options.push_back("manage reservations");
            options.push_back("close program");

            std::string option_header = "Please select an option from the list.";
            auto option_r = Fascades::UiFascade::print_options_and_get_result(options, option_header);

            if(option_r.has_error())
            {
                auto blub = Fascades::UiFascade::write_string(option_r.error());
                continue;
            }
            
            switch (option_r.value())
            {
                case 1:
                {
                    ConfigTablesMenu tablesMenu;
                    auto show_r = Fascades::UiFascade::showMenu(tablesMenu);
                }
                    break;
                case 2:
                    /* code */
                    break;
                case 3:
                    repeat = false;
                default:
                    repeat = false;
                    break;
            }
        }

        return;
    }
}