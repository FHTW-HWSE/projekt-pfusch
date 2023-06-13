#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class DeleteReservation : public MenuBase
    {
        private:

        public:
            DeleteReservation(){};
            ~DeleteReservation(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
