#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class ConfigTablesMenu : public MenuBase
    {
        public:
            ConfigTablesMenu(){};
            ~ConfigTablesMenu(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
