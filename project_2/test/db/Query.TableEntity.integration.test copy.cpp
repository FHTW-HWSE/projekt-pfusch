#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <string>

#include "MainTest.hpp"
#include "test.hpp"
#include "Enviroment.hpp"
#include "TableEntity.hpp"
#include "Query.hpp"

SCENARIO("Query Reservation Entity")
{
    Enviroment_actual();
    auto init_enviroment = Enviroment::Config::instance()->get_db_con()->init_db();

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

            Entities::TableEntity table(0,0,0);
            auto r_create = DataBase::Query::create_table(table);

            std::vector<std::unique_ptr<Entities::BaseEntity>> tables;
            auto r_read = DataBase::Query::read_tables_by_id(tables, table);

			THEN("table is svaed in the DB")
			{
				REQUIRE(r_create.has_value() == true);
				REQUIRE(r_create.value() == true);
				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == true);
				REQUIRE(tables.size() == 1);

                std::unique_ptr<Entities::BaseEntity> &blub = tables[0];
                Entities::TableEntity *table_ptr = dynamic_cast<Entities::TableEntity *>(blub.get());
				REQUIRE(table_ptr != nullptr);
				
                REQUIRE(table.id == table_ptr->id);
				REQUIRE(table.x == table_ptr->x);
				REQUIRE(table.y == table_ptr->y);
				REQUIRE(table.capacity == table_ptr->capacity);
			}
		}

        clear_db();
	}


	Enviroment_mock();
}