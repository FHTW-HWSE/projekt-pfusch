#include "InteractionMock.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <ios>

namespace Interaction
{
    static void push_bool_string
    (
        std::queue<std::unique_ptr<cpp::result<bool, std::string>>> &queue, 
        const cpp::result<bool, std::string> &result
    )
    {
        queue.push(std::make_unique<cpp::result<bool, std::string>>(result));
    }

    static auto pop_bool_string(std::queue<std::unique_ptr<cpp::result<bool, std::string>>> &queue) noexcept -> cpp::result<bool, std::string>
    {
        if(queue.size() == 0)
        {
            return cpp::fail("no mock objects provided");
        }

        auto item = std::move(queue.front());
        queue.pop();

        return *item;
    }

    static void push_int_string
    (
        std::queue<std::unique_ptr<cpp::result<int, std::string>>> &queue, 
        const cpp::result<int, std::string> &result
    )
    {
        queue.push(std::make_unique<cpp::result<int, std::string>>(result));
    }

    static auto pop_int_string(std::queue<std::unique_ptr<cpp::result<int, std::string>>> &queue) noexcept -> cpp::result<int, std::string>
    {
        if(queue.size() == 0)
        {
            return cpp::fail("no mock objects provided");
        }

        auto item = std::move(queue.front());
        queue.pop();

        return *item;
    }

    void InteractionMock::mock_showMenu(const cpp::result<bool, std::string> &result)
    {
        push_bool_string(this->showMenu_queue, result);
    }


    auto InteractionMock::showMenu(UiMenu::MenuBase &menu) noexcept -> cpp::result<bool, std::string>
    {
        const auto r = pop_bool_string(this->showMenu_queue); 

        if(r.has_error())
        {
            return cpp::fail(r.error());
        }

        return r.value();
    }

    void InteractionMock::mock_get_int(const cpp::result<int, std::string> &result)
    {
        push_int_string(this->get_int_queue, result);
    }

    auto InteractionMock::get_int() noexcept -> cpp::result<int, std::string>
    {
        const auto r = pop_int_string(this->get_int_queue); 

        if(r.has_error())
        {
            return cpp::fail(r.error());
        }

        return r.value();
    }

    void InteractionMock::mock_write_string(const cpp::result<bool, std::string> &result)
    {
        push_bool_string(this->write_string_queue, result);
    }


    auto InteractionMock::write_string(const std::string &str) noexcept -> cpp::result<bool, std::string>
    {
        const auto r = pop_bool_string(this->write_string_queue); 

        if(r.has_error())
        {
            return cpp::fail(r.error());
        }

        return r.value();
    }

    void InteractionMock::mock_print_options_and_get_result(const cpp::result<int, std::string> &result)
    {
        push_int_string(this->print_options_and_get_result_queue, result);
    }

    auto InteractionMock::print_options_and_get_result(std::vector<std::string> &options) noexcept -> cpp::result<int, std::string>
    {
        const auto r = pop_int_string(this->print_options_and_get_result_queue); 

        if(r.has_error())
        {
            return cpp::fail(r.error());
        }

        return r.value();
    }
}