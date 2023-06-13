#pragma once

#include <queue>

#include "Base.hpp"
#include "InteractionBase.hpp"

namespace Interaction
{
    class InteractionMock : public InteractionBase
    {
        private:

        std::queue<std::unique_ptr<cpp::result<int, std::string>>> get_int_queue;
        std::queue<std::unique_ptr<cpp::result<int, std::string>>> print_options_and_get_result_queue;
        std::queue<std::unique_ptr<cpp::result<std::string, std::string>>> get_string_queue;

        public:
            InteractionMock(){};
            virtual ~InteractionMock(){};

            void mock_get_int(const cpp::result<int, std::string> &result);
            void mock_print_options_and_get_result(const cpp::result<int, std::string> &result);
            void mock_get_string(const cpp::result<std::string, std::string> &result);

            virtual void showMenu(UiMenu::MenuBase &menu) override;
            virtual auto get_int() noexcept -> cpp::result<int, std::string> override;
            virtual void print_string(const std::string &str) override;
            virtual auto print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string> override;
            virtual auto get_string() noexcept -> cpp::result<std::string, std::string>;
    };
}