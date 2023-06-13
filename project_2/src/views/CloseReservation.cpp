#include "Base.hpp"
#include "CloseReservation.hpp"
#include "UiFascade.hpp"
#include "DbFascade.hpp"
#include "conversion_helper.hpp"

namespace UiMenu
{
    void CloseReservation::show()
    {
        std::vector<std::unique_ptr<Entities::ReservationEntity>> reservations;

        auto r_res = Fascades::DbFascade::get_all_open_reservations(reservations);

        if(r_res.has_error())
        {
            Fascades::UiFascade::print_string(r_res.error());
            return;
        }

        if(reservations.size() == 0)
        {
            Fascades::UiFascade::print_string("There are currently no open reservations");
            return;
        }

        std::vector<std::string> options;

        for (const auto &r : reservations)
        {
            options.push_back(r.get()->to_string());
        }

        auto r_selection = Fascades::UiFascade::print_options_and_get_result(options, "please select a reservatin to close");

        if(r_selection.has_error())
        {
            Fascades::UiFascade::print_string(r_selection.error());
        }

        time_t now = Helper::get_time_now();

        const auto &reservation = reservations.at(r_selection.value());

        reservation.get()->end_time = now;

        auto r_update = Fascades::DbFascade::update_reservation(*reservation);

        if(r_update.has_error())
        {
            Fascades::UiFascade::print_string(r_update.error());
        }

        Fascades::UiFascade::print_string("reservation closed.");
        
        return;
    }
}