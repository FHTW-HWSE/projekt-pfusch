#include "ConfigReservations.hpp"
#include "CreateReservation.hpp"
#include "ListAllReservatins.hpp"
#include "ListAllOpenReservatins.hpp"
#include "ListContactPersonsAroundReservation.hpp"
#include "CloseReservation.hpp"
#include "DeleteReservation.hpp"
#include "UiFascade.hpp"
#include "DbFascade.hpp"

namespace UiMenu
{
    void ConfigReservationsMenu::show()
    {
        bool repeat = true;

        while (repeat)
        {
            std::vector<std::string> options;
            options.push_back("create reservation");                                            //0
            options.push_back("list all reservations");                                         //1
            options.push_back("list all open reservations");                                    //2
            options.push_back("list all contact persons within radius of another reservation"); //3
            options.push_back("close reservation");                                             //4
            options.push_back("delete reservation");                                            //5
            options.push_back("close menu");                                                    //6

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
                    UiMenu::CreateReservation create;
                    Fascades::UiFascade::showMenu(create);
                }
                break;
            case 1:
                {
                    UiMenu::ListAllReservatins list;
                    Fascades::UiFascade::showMenu(list);
                }
                break;
            case 2:
                {
                    UiMenu::ListAllOpenReservatins open_res;
                    Fascades::UiFascade::showMenu(open_res);
                }
                break;
            case 3:
                {
                    UiMenu::ListContactPersonsAroundReservation list_contact_person;
                    Fascades::UiFascade::showMenu(list_contact_person);
                }
                break;
            case 4:
                {
                    UiMenu::CloseReservation close;
                    Fascades::UiFascade::showMenu(close);
                }
                break;
            case 5:
                {
                    UiMenu::DeleteReservation del;
                    Fascades::UiFascade::showMenu(del);
                }
                break;
            case 6:
                repeat = false;
                break;
            
            default:
                repeat = false;
                break;
            }
        }

        return;
    }
}