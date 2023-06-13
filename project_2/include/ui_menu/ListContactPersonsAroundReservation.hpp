#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class ListContactPersonsAroundReservation : public MenuBase
    {
        private:

        public:
            ListContactPersonsAroundReservation(){};
            ~ListContactPersonsAroundReservation(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
