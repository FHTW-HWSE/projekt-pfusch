#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class ListAllReservatins : public MenuBase
    {
        private:

        public:
            ListAllReservatins(){};
            ~ListAllReservatins(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
