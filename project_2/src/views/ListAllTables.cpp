#include "Base.hpp"
#include "ListAllTables.hpp"
#include "UiFascade.hpp"
#include "DbFascade.hpp"
#include "conversion_helper.hpp"

namespace UiMenu
{
    void ListAllTables::show()
    {
        std::vector<std::unique_ptr<Entities::TableEntity>> tables;

        auto r_res = Fascades::DbFascade::get_all_tables(tables);

        if(r_res.has_error())
        {
            Fascades::UiFascade::print_string(r_res.error());
            return;
        }

        if(tables.size() == 0)
        {
            Fascades::UiFascade::print_string("There are currently no saved tables");
            return;
        }

        for (const auto &r : tables)
        {
            Fascades::UiFascade::print_string(r.get()->to_string());
        }
        
        return;
    }
}