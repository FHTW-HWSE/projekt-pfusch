#pragma once

#include "Base.hpp"
#include "UiMenuBase.hpp"

namespace UiMenu
{
    class CreateTable : public MenuBase
    {
        private:

        public:
            CreateTable(){};
            ~CreateTable(){};
            //overrides
            virtual void show() override;
    };
    
} // namespace UiMenu
