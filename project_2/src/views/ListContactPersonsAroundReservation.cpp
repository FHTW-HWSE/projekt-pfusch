#include "Base.hpp"
#include "ListContactPersonsAroundReservation.hpp"
#include "UiFascade.hpp"
#include "DbFascade.hpp"
#include "conversion_helper.hpp"

namespace UiMenu
{
    void ListContactPersonsAroundReservation::show()
    {
        std::vector<std::unique_ptr<Entities::ReservationEntity>> reservations;

        auto r_res = Fascades::DbFascade::get_all_reservations(reservations);

        if(r_res.has_error())
        {
            Fascades::UiFascade::print_string(r_res.error());
            return;
        }

        if(reservations.size() == 0)
        {
            Fascades::UiFascade::print_string("There are currently no saved reservations");
            return;
        }

        std::vector<std::string> options;

        for(const auto &r : reservations)
        {
            options.push_back(r.get()->to_string());
        }

        auto r_opt = Fascades::UiFascade::print_options_and_get_result(options, "please select the reservation you want to search for");

        if(r_opt.has_error())
        {
            Fascades::UiFascade::print_string(r_opt.error());
            return;
        }

        Fascades::UiFascade::print_string("please input the search radius as an integer");
        auto r_radius = Fascades::UiFascade::get_int();

        if(r_radius.has_error())
        {
            Fascades::UiFascade::print_string(r_radius.error());
            return;
        }

        std::vector<std::unique_ptr<Entities::ReservationEntity>> found_res;
        auto r_found = Fascades::DbFascade
            ::get_reservations_within_radius_of_reservation
            (
                found_res, 
                *(reservations.at(r_opt.value())),
                r_radius.value()
            );

        if(r_found.has_error())
        {
            Fascades::UiFascade::print_string(r_found.error());
            return;
        }

        if(found_res.size() == 0)
        {
            Fascades::UiFascade::print_string("there are no reservations that match the criteria");
            return;
        }

        for (const auto &r : found_res)
        {
            Fascades::UiFascade::print_string(r.get()->to_string());
        }
        
        return;
    }
}