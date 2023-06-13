#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class DeleteTable : public MenuBase
    {
        private:

        public:
            DeleteTable(){};
            ~DeleteTable(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
