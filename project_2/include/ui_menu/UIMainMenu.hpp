#pragma once

#include "UiMenuBase.hpp"

namespace UiMenu
{
    class MainMenu : public MenuBase
    {
        public:
            MainMenu();
            ~MainMenu();
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
