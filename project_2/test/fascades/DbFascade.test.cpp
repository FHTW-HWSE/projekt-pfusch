#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <string>

#include "DbFascade.hpp"
#include "Enviroment.hpp"
#include "DbCrudMock.hpp"
#include "TableEntity.hpp"
#include "Query.hpp"

SCENARIO("Db_fascade")
{
    auto crud = Enviroment::Config::instance()->get_db_con()->get_crud();
    DataBase::DbCrudMock *crud_ptr = dynamic_cast<DataBase::DbCrudMock*>(crud);

	GIVEN("user wants to get a table by x y")
	{
        Entities::TableEntity source(1, 1, 1);
        std::vector<std::unique_ptr<Entities::BaseEntity>> source1;
        source1.push_back(std::make_unique<Entities::TableEntity>(source));

		WHEN("get table by x y")
		{
            const auto r = cpp::result<bool, std::string> {true};
            crud_ptr->mock_read_records(r, source1);

            std::vector<std::unique_ptr<Entities::TableEntity>> tables;
            auto result = Fascades::DbFascade::get_tables_by_x_y(tables, source.x, source.y);
            
			THEN("table is svaed in the DB")
			{
                REQUIRE(result.has_value() == true);
                REQUIRE(result.value() == true);
                REQUIRE(tables.size() == 1);
                REQUIRE(source1.size() == tables.size());

                while (tables.empty() == false)
                {
                    auto s = std::move(source1.back());
                    source1.pop_back();
                    auto t = std::move(tables.back());
                    tables.pop_back();

                    auto *s_ptr = dynamic_cast<Entities::TableEntity*>(s.get());

                    REQUIRE(s_ptr != nullptr);
                    REQUIRE((*s_ptr) == *t);
                }
			}
		}
	}

    GIVEN("user wants to get a table by id")
	{
        Entities::TableEntity source(1, 1, 1);
        std::vector<std::unique_ptr<Entities::BaseEntity>> source1;
        source1.push_back(std::make_unique<Entities::TableEntity>(source));

		WHEN("get table by id")
		{
            const auto r = cpp::result<bool, std::string> {true};
            crud_ptr->mock_read_records(r, source1);

            std::vector<std::unique_ptr<Entities::TableEntity>> tables;
            auto result = Fascades::DbFascade::get_tables_by_id(tables, source.id);
            
			THEN("table is read from DB")
			{
                REQUIRE(result.has_value() == true);
                REQUIRE(result.value() == true);
                REQUIRE(tables.size() == 1);
                REQUIRE(source1.size() == tables.size());

                while (tables.empty() == false)
                {
                    auto s = std::move(source1.back());
                    source1.pop_back();
                    auto t = std::move(tables.back());
                    tables.pop_back();

                    auto *s_ptr = dynamic_cast<Entities::TableEntity*>(s.get());

                    REQUIRE(s_ptr != nullptr);
                    REQUIRE((*s_ptr) == *t);
                }
			}
		}
	}

    GIVEN("user wants to get all tables")
	{
        Entities::TableEntity source1(1, 1, 1);
        Entities::TableEntity source2(2, 2, 2);
        Entities::TableEntity source3(3, 3, 3);

        std::vector<std::unique_ptr<Entities::BaseEntity>> sources;
        sources.push_back(std::make_unique<Entities::TableEntity>(source1));
        sources.push_back(std::make_unique<Entities::TableEntity>(source2));
        sources.push_back(std::make_unique<Entities::TableEntity>(source3));

		WHEN("get all tables")
		{
            const auto r = cpp::result<bool, std::string> {true};
            crud_ptr->mock_read_all_records(r, sources);

            std::vector<std::unique_ptr<Entities::TableEntity>> tables;
            auto result = Fascades::DbFascade::get_all_tables(tables);
            
			THEN("tables are read from DB")
			{
                REQUIRE(result.has_value() == true);
                REQUIRE(result.value() == true);
                REQUIRE(tables.size() == 3);
                REQUIRE(sources.size() == tables.size());

                while (tables.empty() == false)
                {
                    auto s = std::move(sources.back());
                    sources.pop_back();
                    auto t = std::move(tables.back());
                    tables.pop_back();

                    auto *s_ptr = dynamic_cast<Entities::TableEntity*>(s.get());

                    REQUIRE(s_ptr != nullptr);
                    REQUIRE((*s_ptr) == *t);
                }
			}
		}
	}

    GIVEN("user wants to create a table")
	{
        Entities::TableEntity source1(0, 0, 0);

        auto result = GENERATE
        (
            as<cpp::result<bool, std::string>>{},
            cpp::result<bool, std::string>{true},
            cpp::result<bool, std::string>{false}
        );

		WHEN("creates table")
		{
            Entities::TableEntity source1(1, 1, 1);
            Entities::TableEntity source2(2, 2, 2);
            Entities::TableEntity source3(3, 3, 3);

            std::vector<std::unique_ptr<Entities::BaseEntity>> sources;
            sources.push_back(std::make_unique<Entities::TableEntity>(source1));
            sources.push_back(std::make_unique<Entities::TableEntity>(source2));
            sources.push_back(std::make_unique<Entities::TableEntity>(source3));

            const auto r_1 = cpp::result<bool, std::string> {true};
            crud_ptr->mock_read_all_records(r_1, sources);

            const auto r_2 = result;
            crud_ptr->mock_create_record(r_2);

            auto update_result = Fascades::DbFascade::create_table(source1);
            
			THEN("table is created in DB")
			{
                REQUIRE(result.has_value() == update_result.has_value());

                if(result.has_value())
                {
                    REQUIRE(result.value() == update_result.value());
                }
                else
                {
                    REQUIRE(result.error() == update_result.error());
                }
			}
		}
	}

    GIVEN("user wants to update a table")
	{
        Entities::TableEntity source1(1, 1, 1);

        auto result = GENERATE
        (
            as<cpp::result<bool, std::string>>{},
            cpp::result<bool, std::string>{true},
            cpp::result<bool, std::string>{false}
        );

		WHEN("update table")
		{
            const auto r = result;
            crud_ptr->mock_update_record(r);

            auto update_result = Fascades::DbFascade::update_table(source1);
            
			THEN("table is updated in DB")
			{
                REQUIRE(result.has_value() == update_result.has_value());

                if(result.has_value())
                {
                    REQUIRE(result.value() == update_result.value());
                }
                else
                {
                    REQUIRE(result.error() == update_result.error());
                }
			}
		}
	}

    GIVEN("user wants to delete a table")
	{
        Entities::TableEntity source1(1, 1, 1);

        auto result = GENERATE
        (
            as<cpp::result<bool, std::string>>{},
            cpp::result<bool, std::string>{true},
            cpp::result<bool, std::string>{false}
        );

		WHEN("delete table")
		{
            const auto r = result;
            crud_ptr->mock_delete_record(r);

            auto update_result = Fascades::DbFascade::delete_table(source1);
            
			THEN("table is deleted in DB")
			{
                REQUIRE(result.has_value() == update_result.has_value());

                if(result.has_value())
                {
                    REQUIRE(result.value() == update_result.value());
                }
                else
                {
                    REQUIRE(result.error() == update_result.error());
                }
			}
		}
	}
}