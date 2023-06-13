#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class ConfigReservationsMenu : public MenuBase
    {
        private:

        public:
            ConfigReservationsMenu(){};
            ~ConfigReservationsMenu(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
