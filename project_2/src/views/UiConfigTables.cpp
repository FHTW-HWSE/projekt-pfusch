#include "ConfigTablesMenu.hpp"
#include "UiFascade.hpp"
#include "DbFascade.hpp"

namespace UiMenu
{
    void ConfigTablesMenu::show()
    {
        bool repeat = true;

        while (repeat)
        {
            std::vector<std::string> options;
            options.push_back("create table");
            options.push_back("list all tables");
            options.push_back("update table");
            options.push_back("delete table");
            options.push_back("close menu");

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
                    auto create_r = this->createTable();

                    if(create_r.has_error())
                    {
                        //do something
                    }
                }
                    break;
                case 2:
                    /* code */
                    break;
                case 3:
                    /* code */
                case 4:
                    break;
                case 5:
                    repeat = false;
                default:
                    break;
            }
        }

        return;
    }

    auto ConfigTablesMenu::createTable() noexcept -> cpp::result<bool, std::string>
    {
        //get x coordinate

        //get y coordinate

        //get capacity

        // Entities::TableEntity table(0, 0, 0);

        //write Table to DB

        //return result

        return cpp::fail("not implememnted");
    }
}