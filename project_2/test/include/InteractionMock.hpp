#pragma once

#include <queue>

#include "Base.hpp"
#include "InteractionBase.hpp"

namespace Interaction
{
    class InteractionMock : public InteractionBase
    {
        private:

        std::queue<std::unique_ptr<cpp::result<bool, std::string>>> showMenu_queue;
        std::queue<std::unique_ptr<cpp::result<int, std::string>>> get_int_queue;
        std::queue<std::unique_ptr<cpp::result<bool, std::string>>> write_string_queue;
        std::queue<std::unique_ptr<cpp::result<int, std::string>>> print_options_and_get_result_queue;

        public:
            InteractionMock(){};
            virtual ~InteractionMock(){};

            void mock_showMenu(const cpp::result<bool, std::string> &result);
            void mock_get_int(const cpp::result<int, std::string> &result);
            void mock_write_string(const cpp::result<bool, std::string> &result);
            void mock_print_options_and_get_result(const cpp::result<int, std::string> &result);


            virtual auto showMenu(UiMenu::MenuBase &menu) noexcept -> cpp::result<bool, std::string> override;
            virtual auto get_int() noexcept -> cpp::result<int, std::string> override;
            virtual auto write_string(const std::string &str) noexcept -> cpp::result<bool, std::string> override;
            virtual auto print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string> override;
    };
}