#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <string>
#include <stdlib.h>

#include "Base.hpp"
#include "Enviroment.hpp"
#include "UiFascade.hpp"
#include "InteractionMock.hpp"
#include "UIMainMenu.hpp"

SCENARIO("UiFascade")
{
    auto inter_ptr = Enviroment::Config::instance()->get_interaction();
    auto inter = dynamic_cast<Interaction::InteractionMock *>(inter_ptr);

	GIVEN("show a menu")
	{
		WHEN("show menu")
		{
            const auto r = cpp::result<bool, std::string>{true};

            inter->mock_showMenu(r);
            
            UiMenu::MainMenu menu;

			THEN("menu is shown")
			{
                auto show_r = Fascades::UiFascade::showMenu(menu);
                
                REQUIRE(r == show_r);
			}
		}
	}

    GIVEN("get int")
	{
		WHEN("get int")
		{
            const auto r = cpp::result<int, std::string>{1};

            inter->mock_get_int(r);
            
            UiMenu::MainMenu menu;

			THEN("int is returned")
			{
                auto show_r = Fascades::UiFascade::get_int();
            
                REQUIRE(r.has_value() == show_r.has_value());
                REQUIRE(r.value() == show_r.value());
			}
		}
	}

    GIVEN("write_string")
	{
		WHEN("write_string")
		{
            const auto r = cpp::result<bool, std::string>{true};

            inter->mock_write_string(r);
            
            UiMenu::MainMenu menu;

			THEN("string is wirten")
			{
                std::string msg = "nah";
                auto show_r = Fascades::UiFascade::write_string(msg);
            
                REQUIRE(r.has_value() == show_r.has_value());
                REQUIRE(r.value() == show_r.value());
			}
		}
	}

    GIVEN("print options and get answer")
	{
		WHEN("print options and get answer")
		{
            const auto r = cpp::result<int, std::string>{1};

            inter->mock_print_options_and_get_result(r);
            
            UiMenu::MainMenu menu;

			THEN("print options and get answer")
			{
                std::vector<std::string> options;
                auto show_r = Fascades::UiFascade::print_options_and_get_result(options);
            
                REQUIRE(r.has_value() == show_r.has_value());
                REQUIRE(r.value() == show_r.value());
			}
		}
	}
}