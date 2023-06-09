#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class ConfigTablesMenu : public MenuBase
    {
        private:
            auto createTable() noexcept -> cpp::result<bool, std::string>;

        public:
            ConfigTablesMenu(){};
            ~ConfigTablesMenu(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
