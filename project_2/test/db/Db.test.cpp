#include <catch2/catch.hpp>
#include <string>

#include "test.hpp"
#include "DbConnector.hpp"

#include "Queries.hpp"

SCENARIO("Queries")
{
    DataBase::DbConnector::init_connector(DB_PATH);
    auto meh = DataBase::DbConnector::instance()->init_db_structure();

	GIVEN("want to save table")
	{
		auto table = GENERATE
        (
            as<Entities::TableEntity>{},
            Entities::TableEntity(0,0,0),
            Entities::TableEntity(1,1,1),
            Entities::TableEntity(2,2,2)
        );

        DataBase::DbConnector::instance()->drop_db();

		WHEN("saves table")
		{

            std::unique_ptr<Entities::BaseEntity> ptr = std::make_unique<Entities::TableEntity>(table);
            auto r_create = DataBase::Queries::create_table(ptr);

            std::vector<std::unique_ptr<Entities::BaseEntity>> tables;
            auto r_read = DataBase::Queries::read_tables_by_id(tables, ptr);

			THEN("table is svaed in the DB")
			{
                bool result = 
                    r_create.has_value() 
                    && r_create.value()
                    && r_read.has_value()
                    && r_read.value()
                    && tables.size() == 1;

				REQUIRE(result == true);
			}
		}

        DataBase::DbConnector::instance()->drop_db();
	}

    GIVEN("want to read table by id")
	{
		auto table = GENERATE
        (
            as<Entities::TableEntity>{},
            Entities::TableEntity(0,0,0),
            Entities::TableEntity(1,1,1),
            Entities::TableEntity(2,2,2)
        );

        DataBase::DbConnector::instance()->drop_db();

		WHEN("reads table")
		{

            std::unique_ptr<Entities::BaseEntity> ptr = std::make_unique<Entities::TableEntity>(table);
            auto r_create = DataBase::Queries::create_table(ptr);

            std::vector<std::unique_ptr<Entities::BaseEntity>> tables;
            auto r_read = DataBase::Queries::read_tables_by_id(tables, ptr);

			THEN("table is read from the DB")
			{
                bool result = 
                    r_create.has_value() 
                    && r_create.value()
                    && r_read.has_value()
                    && r_read.value()
                    && tables.size() == 1;

				REQUIRE(result == true);
			}
		}

        DataBase::DbConnector::instance()->drop_db();
	}

    GIVEN("want to read table by x y")
	{
		auto table = GENERATE
        (
            as<Entities::TableEntity>{},
            Entities::TableEntity(0,0,0),
            Entities::TableEntity(1,1,1),
            Entities::TableEntity(2,2,2)
        );

        DataBase::DbConnector::instance()->drop_db();

		WHEN("read table by x y")
		{

            std::unique_ptr<Entities::BaseEntity> ptr = std::make_unique<Entities::TableEntity>(table);
            auto r_create = DataBase::Queries::create_table(ptr);

            std::vector<std::unique_ptr<Entities::BaseEntity>> tables;
            auto r_read = DataBase::Queries::read_tables_by_x_y(tables, ptr);

			THEN("table is read from the DB")
			{
                bool result = 
                    r_create.has_value() 
                    && r_create.value()
                    && r_read.has_value()
                    && r_read.value()
                    && tables.size() == 1;

				REQUIRE(result == true);
			}
		}

        DataBase::DbConnector::instance()->drop_db();
	}
}