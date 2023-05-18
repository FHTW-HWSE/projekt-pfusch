#include <catch2/catch.hpp>
#include <string>

#define private public

#include "DbConnector.hpp"

SCENARIO("DbConnector")
{
	GIVEN("no connector initialized 01")
	{
		WHEN("call has_instance")
		{
			THEN("the function returns false")
			{
				auto has_instance = DataBase::DbConnector::has_instance();
				REQUIRE(has_instance == false);
			}
		}
	}

	GIVEN("no connector initialized 02")
	{
		WHEN("call instance")
		{
			THEN("returns a nullptr")
			{
				auto instance = DataBase::DbConnector::instance();
				REQUIRE(instance == nullptr);
			}
		}
	}

	GIVEN("no connector initialized 03")
	{
		auto path = GENERATE(as<std::string>{}, "./", "some/path");

		WHEN("init connector")
		{
			DataBase::DbConnector::init_connector(path);
			THEN("the init path is stored in the connector")
			{
				auto str = DataBase::DbConnector::instance()->get_connection_string();
				REQUIRE(str == path);
			}
		}
	}

	GIVEN("connector is initialized 01")
	{
		std::string path = "./";
		DataBase::DbConnector::init_connector(path);

		WHEN("call has_instance")
		{
			THEN("the function returns false")
			{
				auto has_instance = DataBase::DbConnector::has_instance();
				REQUIRE(has_instance == true);
			}
		}
	}
}