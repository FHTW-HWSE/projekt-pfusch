#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class CloseReservation : public MenuBase
    {
        private:

        public:
            CloseReservation(){};
            ~CloseReservation(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
