#include "Base.hpp"
#include "DeleteTable.hpp"
#include "UiFascade.hpp"
#include "DbFascade.hpp"
#include "conversion_helper.hpp"

namespace UiMenu
{
    void DeleteTable::show()
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

        const auto &table = tables.at(r_select.value());

        auto r_update = Fascades::DbFascade::delete_table(*table);

        if(r_update.has_error())
        {
            Fascades::UiFascade::print_string(r_update.error());
            return;
        }

        Fascades::UiFascade::print_string("Table deleted");

        return;
    }
}