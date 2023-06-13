#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class CreateReservation : public MenuBase
    {
        private:

        public:
            CreateReservation(){};
            ~CreateReservation(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
