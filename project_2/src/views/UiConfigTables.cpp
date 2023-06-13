#include "ConfigTablesMenu.hpp"
#include "ListAllTables.hpp"
#include "UpdateTable.hpp"
#include "DeleteTable.hpp"
#include "UiFascade.hpp"
#include "DbFascade.hpp"
#include "CreateTable.hpp"

namespace UiMenu
{
    void ConfigTablesMenu::show()
    {
        bool repeat = true;

        while (repeat)
        {
            std::vector<std::string> options;
            options.push_back("create table");      //0
            options.push_back("list all tables");   //1
            options.push_back("update table");      //2
            options.push_back("delete table");      //3
            options.push_back("close menu");        //4

            std::string option_header = "Please select an option from the list.";
            auto option_r = Fascades::UiFascade::print_options_and_get_result(options, option_header);

            if(option_r.has_error())
            {
                Fascades::UiFascade::print_string(option_r.error());
                continue;
            }
            
            switch (option_r.value())
            {
                case 0:
                {
                    UiMenu::CreateTable create;
                    Fascades::UiFascade::showMenu(create);
                }
                    break;
                case 1:
                {
                    UiMenu::ListAllTables list_all;
                    Fascades::UiFascade::showMenu(list_all);
                }
                    break;
                case 2:
                {
                    UiMenu::UpdateTable update;
                    Fascades::UiFascade::showMenu(update);
                }
                    break;
                case 3:
                {
                    UiMenu::DeleteTable delete_table;
                    Fascades::UiFascade::showMenu(delete_table);
                }
                    break;
                case 4:
                    repeat = false;
                default:
                    break;
            }
        }

        return;
    }
}