#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class UpdateTable : public MenuBase
    {
        private:

        public:
            UpdateTable(){};
            ~UpdateTable(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
