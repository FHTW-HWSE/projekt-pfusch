#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class ListAllTables : public MenuBase
    {
        private:

        public:
            ListAllTables(){};
            ~ListAllTables(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
