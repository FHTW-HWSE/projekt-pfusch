#include "Base.hpp"
#include "ListAllReservatins.hpp"
#include "UiFascade.hpp"
#include "DbFascade.hpp"
#include "conversion_helper.hpp"

namespace UiMenu
{
    void ListAllReservatins::show()
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

        for (const auto &r : reservations)
        {
            Fascades::UiFascade::print_string(r.get()->to_string());
        }
        
        return;
    }
}