#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class ListAllOpenReservatins : public MenuBase
    {
        private:

        public:
            ListAllOpenReservatins(){};
            ~ListAllOpenReservatins(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
