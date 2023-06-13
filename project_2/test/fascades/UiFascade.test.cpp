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
            UiMenu::MainMenu menu;

			THEN("menu is shown")
			{
                Fascades::UiFascade::showMenu(menu);
                
                REQUIRE(true == true);
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

    GIVEN("print_string")
	{
		WHEN("print_string")
		{            
            UiMenu::MainMenu menu;

			THEN("string is wirten")
			{
                std::string msg = "nah";
                Fascades::UiFascade::print_string(msg);
            
                REQUIRE(true == true);
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

	GIVEN("want to get string from user")
	{
		WHEN("get string from user")
		{

			auto res = GENERATE_COPY
			(
				cpp::result<std::string, std::string>{"unit test tring"},
				cpp::fail("some error message")
			);

			std::string str = "unit test string";
            const auto r = cpp::result<std::string, std::string>{str};

			inter->mock_get_string(r);

			auto r_str = inter->get_string();

			THEN("string is fetched from user")
			{
				if(res.has_error())
				{
					REQUIRE(r_str.has_error());
					REQUIRE(r_str.error().compare(res.error()) == true);
				}
				else
				{
					REQUIRE(r_str.has_value());
					REQUIRE(r_str.value().compare(res.value()) == true);
				}
			}

		}
	}
}