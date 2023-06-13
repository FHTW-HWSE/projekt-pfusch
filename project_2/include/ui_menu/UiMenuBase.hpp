#pragma once

namespace UiMenu
{
    class MenuBase
    {
        public:
            virtual ~MenuBase(){};
            virtual void show() = 0;
    };
    
} // namespace UiMenu
