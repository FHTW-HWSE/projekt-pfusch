#include "Base.hpp"
#include "CreateReservation.hpp"
#include "UiFascade.hpp"
#include "DbFascade.hpp"
#include "conversion_helper.hpp"

namespace UiMenu
{
    void CreateReservation::show()
    {
        bool repeat = true;

        std::vector<std::unique_ptr<::Entities::TableEntity>> tables;
        auto r_all_tables = Fascades::DbFascade::get_all_tables(tables);

        if(r_all_tables.has_error())
        {
            Fascades::UiFascade::print_string(r_all_tables.error());
            return;
        }

        if(tables.size() == 0)
        {
            Fascades::UiFascade::print_string("There are no Tables configured. Please add a table.");
            return;
        }

        std::vector<std::string> options;

        for(const auto &t : tables)
        {
            options.push_back(t.get()->to_string());
        }

        auto r_selection = Fascades::UiFascade::print_options_and_get_result(options, "Select a table from the list.");

        if(r_selection.has_error())
        {
            Fascades::UiFascade::print_string(r_selection.error());
            return;
        }

        Fascades::UiFascade::print_string("input the email adress of the contact person.");
        auto r_email = Fascades::UiFascade::get_email();

        if(r_email.has_error())
        {
            Fascades::UiFascade::print_string(r_email.error());
            return;
        }

        const auto &table = tables.at(r_selection.value());

        Entities::ReservationEntity reservation(*table, Helper::get_time_now(), 0, r_email.value());

        auto r_save = Fascades::DbFascade::create_reservation(reservation);

        if(r_save.has_error())
        {
            Fascades::UiFascade::print_string(r_save.error());
        }

        Fascades::UiFascade::print_string("reservation saved.");

        return;
    }
}