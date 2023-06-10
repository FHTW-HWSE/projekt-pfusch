#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <string>

#include "MainTest.hpp"
#include "test.hpp"
#include "Enviroment.hpp"
#include "TableEntity.hpp"
#include "DbFascade.hpp"

SCENARIO("Query TableEntity")
{
    Enviroment_actual();

	GIVEN("want to save table")
	{
		auto table = GENERATE
        (
            as<Entities::TableEntity>{},
            Entities::TableEntity(0,0,0),
            Entities::TableEntity(1,1,1),
            Entities::TableEntity(2,2,2)
        );

        clear_db();

		WHEN("saves table")
		{

            auto r_create = Fascades::DbFascade::create_table(table);

            std::vector<std::unique_ptr<Entities::TableEntity>> tables;
            auto r_read = Fascades::DbFascade::get_tables_by_id(tables, table.id);

			THEN("table is svaed in the DB")
			{
				REQUIRE(r_create.has_value() == true);
				REQUIRE(r_create.value() == true);
				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == true);
				REQUIRE(tables.size() == 1);

				const auto &table_1 = tables.back();

				REQUIRE(table == *table_1);
			}
		}

        clear_db();
	}

	GIVEN("want to save table")
	{
		auto table = GENERATE
        (
            as<Entities::TableEntity>{},
            Entities::TableEntity(0,0,0),
            Entities::TableEntity(1,1,1),
            Entities::TableEntity(2,2,2)
        );

        clear_db();

		WHEN("table with same x y already exists")
		{

            auto r_create_1 = Fascades::DbFascade::create_table(table);

			table.id = table.create_new_uuid();

            auto r_create_2 = Fascades::DbFascade::create_table(table);

			THEN("table is svaed in the DB")
			{
				REQUIRE(r_create_2.has_error() == true);
			}
		}

        clear_db();
	}

	GIVEN("want to get table by id")
	{
		auto table = GENERATE
        (
            as<Entities::TableEntity>{},
            Entities::TableEntity(0,0,0),
            Entities::TableEntity(1,1,1),
            Entities::TableEntity(2,2,2)
        );

        clear_db();

		WHEN("get table by id")
		{

            auto r_create = Fascades::DbFascade::create_table(table);

            std::vector<std::unique_ptr<Entities::TableEntity>> tables;
            auto r_read = Fascades::DbFascade::get_tables_by_id(tables, table.id);

			THEN("table is read from DB")
			{
				REQUIRE(r_create.has_value() == true);
				REQUIRE(r_create.value() == true);
				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == true);
				REQUIRE(tables.size() == 1);

				const auto &table_1 = tables.back();

				REQUIRE(table == *table_1);
			}
		}

        clear_db();
	}

	GIVEN("want to get table by x y")
	{
		std::vector<std::unique_ptr<Entities::TableEntity>> source;
		source.push_back(std::make_unique<Entities::TableEntity>(1, 1, 1));
		source.push_back(std::make_unique<Entities::TableEntity>(2, 2, 1));

        clear_db();

		WHEN("get table by x y")
		{
			for (const auto &t : source)
			{
            	auto r_create = Fascades::DbFascade::create_table(*t);
			}

            std::vector<std::unique_ptr<Entities::TableEntity>> tables;
            auto r_read = Fascades::DbFascade::get_tables_by_x_y(tables, 1, 1);

			THEN("table is read from DB")
			{
				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == true);
				REQUIRE(tables.size() == 1);

				source.pop_back();

				while (tables.empty() == false)
				{
					const auto &s = source.back();
					const auto &t = tables.back();

					REQUIRE(*s == *t);

					source.pop_back();
					tables.pop_back();
				}
			}
		}

        clear_db();
	}

	GIVEN("want to get all tables")
	{
		std::vector<std::unique_ptr<Entities::TableEntity>> source;
		source.push_back(std::make_unique<Entities::TableEntity>(1, 1, 1));
		source.push_back(std::make_unique<Entities::TableEntity>(2, 2, 2));
		source.push_back(std::make_unique<Entities::TableEntity>(3, 3, 3));
		source.push_back(std::make_unique<Entities::TableEntity>(4, 4, 4));

        clear_db();

		WHEN("get all tables")
		{
			for (const auto &t : source)
			{
            	auto r_create = Fascades::DbFascade::create_table(*t);

				if(r_create.has_error())
				{
					auto msg = r_create.error();
					int nah = 0;
				}
			}

            std::vector<std::unique_ptr<Entities::TableEntity>> tables;
            auto r_read = Fascades::DbFascade::get_all_tables(tables);

			THEN("alls tables are read from DB")
			{
				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == true);
				REQUIRE(tables.size() == source.size());

				while (tables.empty() == false)
				{
					const auto &s = source.back();
					const auto &t = tables.back();

					Entities::TableEntity ss = *s;
					Entities::TableEntity tt = *t;

					REQUIRE(*s == *t);

					source.pop_back();
					tables.pop_back();
				}
			}
		}

        clear_db();
	}



	Enviroment_mock();
}