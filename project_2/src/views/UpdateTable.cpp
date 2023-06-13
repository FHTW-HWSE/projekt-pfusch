#include "Base.hpp"
#include "UpdateTable.hpp"
#include "UiFascade.hpp"
#include "DbFascade.hpp"
#include "conversion_helper.hpp"

namespace UiMenu
{
    void UpdateTable::show()
    {
        std::vector<std::unique_ptr<Entities::TableEntity>> tables;

        auto r_read = Fascades::DbFascade::get_all_tables(tables);

        if(r_read.has_error())
        {
            Fascades::UiFascade::print_string(r_read.error());
            return;
        }

        if(tables.size() == 0)
        {
            Fascades::UiFascade::print_string("There are currently no saved tables");
            return;
        }

        std::vector<std::string> options;

        for (const auto &table : tables)
        {
            options.push_back(table.get()->to_string());
        }

        auto r_select = Fascades::UiFascade::print_options_and_get_result(options, "please select a table");

        if(r_select.has_error())
        {
            Fascades::UiFascade::print_string(r_select.error());
            return;
        }

        Fascades::UiFascade::print_string("input the new x coordinate as an integer");
        auto r_x = Fascades::UiFascade::get_int();

        if(r_x.has_error())
        {
            Fascades::UiFascade::print_string(r_x.error());
        }

        Fascades::UiFascade::print_string("input the new y coordinate as an integer");
        auto r_y = Fascades::UiFascade::get_int();

        if(r_y.has_error())
        {
            Fascades::UiFascade::print_string(r_y.error());
        }

        const auto &table = tables.at(r_select.value());

        table.get()->x = r_x.value();
        table.get()->y = r_y.value();

        auto r_update = Fascades::DbFascade::update_table(*table);

        if(r_update.has_error())
        {
            Fascades::UiFascade::print_string(r_update.error());
            return;
        }

        Fascades::UiFascade::print_string("Table updated with following values:");
        Fascades::UiFascade::print_string(table.get()->to_string());

        return;
    }
}