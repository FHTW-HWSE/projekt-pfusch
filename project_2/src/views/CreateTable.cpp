#include "Base.hpp"
#include "CreateTable.hpp"
#include "UiFascade.hpp"
#include "DbFascade.hpp"
#include "conversion_helper.hpp"

namespace UiMenu
{
    void CreateTable::show()
    {
        bool repeat = true;

        Fascades::UiFascade::print_string("please input the x coordinate as an integer");
        auto r_x = Fascades::UiFascade::get_int();

        if(r_x.has_error())
        {
            Fascades::UiFascade::print_string(r_x.error());
            return;
        }

        Fascades::UiFascade::print_string("please input the y coordinate as an integer");
        auto r_y = Fascades::UiFascade::get_int();

        if(r_y.has_error())
        {
            Fascades::UiFascade::print_string(r_y.error());
            return;
        }

        Entities::TableEntity table(r_x.value(), r_y.value(), 0);

        auto r_create = Fascades::DbFascade::create_table(table);

        if(r_create.has_error())
        {
            Fascades::UiFascade::print_string(r_create.error());
            return;
        }

        Fascades::UiFascade::print_string("Table created");

        return;
    }
}