#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <string>

#include "Base.hpp"
#include "TableEntity.hpp"

SCENARIO("TableEntity")
{
	GIVEN("A Table Entity")
	{
        Entities::TableEntity table1(1,1,1);
        std::string str1 = "x: 1, y: 1";

        Entities::TableEntity table2(2,2,2);
        std::string str2 = "x: 2, y: 2";

		WHEN("user wants to see it in the UI")
		{
            std::string to_str_1 = table1.to_string();
            std::string to_str_2 = table2.to_string();

			THEN("a readable string is created")
			{
                REQUIRE(str1.compare(to_str_1) == true);
                REQUIRE(str2.compare(to_str_2) == true);
			}
		}
	}
}