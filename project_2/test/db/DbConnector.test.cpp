#include <catch2/catch.hpp>
#include <string>
#include "conversion_helper.hpp"

#define private public

#include "DbConnector.hpp"

SCENARIO("DbConnector")
{
	// GIVEN("no connector initialized 01")
	// {
	// 	WHEN("call has_instance")
	// 	{
	// 		THEN("the function returns false")
	// 		{
	// 			auto has_instance = DataBase::DbConnector::has_instance();
	// 			REQUIRE(has_instance == false);
	// 		}
	// 	}
	// }

	// GIVEN("no connector initialized 02")
	// {
	// 	WHEN("call instance")
	// 	{
	// 		THEN("returns defaul path './'")
	// 		{
	// 			auto instance = DataBase::DbConnector::instance();
	// 			REQUIRE(instance->get_connection_string() == "./");
	// 		}
	// 	}
	// }

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

		auto str_time = GENERATE(as<std::string>{}, "2023-05-01", "2023-05-16", "2022-01-01");

		WHEN("call has_instance")
		{
			auto tm = Helper::Ymd_to_tm(str_time);
			auto file_path = DataBase::DbConnector::instance()->get_reservation_path(tm).value();
			
			THEN("the function returns true")
			{
				std::string test_path = "./" + str_time + ".csv";

				REQUIRE(test_path == file_path);
			}
		}
	}
}