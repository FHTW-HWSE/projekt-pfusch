#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <string>

#include "Enviroment.hpp"
#include "DbCrudMock.hpp"
#include "TableEntity.hpp"

SCENARIO("DbCrudMock")
{
    auto crud = Enviroment::Config::instance()->get_db_con()->get_crud();
    DataBase::DbCrudMock *crud_ptr = dynamic_cast<DataBase::DbCrudMock*>(crud);

	GIVEN("mock result provided for crud create")
	{
        auto result = GENERATE
        (
            as<cpp::result<bool, std::string>>{},
            cpp::result<bool, std::string>{true},
            cpp::result<bool, std::string>{false}
        );

		WHEN("create")
		{
            auto r = std::move(result);
            crud_ptr->mock_create_record(r);

            Entities::TableEntity table(0,0,0);
            auto entity = table.clone();

            auto crud_r = crud_ptr->create_record(*entity, "bleh");

			THEN("table is svaed in the DB")
			{
                REQUIRE(r.has_value() == crud_r.has_value());
                REQUIRE(r.value() == crud_r.value());
			}
		}
	}

    GIVEN("multible mock result provided for crud create")
	{
        const auto r_t = cpp::result<bool, std::string>{true};
        const auto r_f = cpp::result<bool, std::string>{false};
        std::string error_msg = "unit test error";
        const auto r_e = cpp::fail(error_msg);

		WHEN("create")
		{
            crud_ptr->mock_create_record(r_t);
            crud_ptr->mock_create_record(r_f);
            crud_ptr->mock_create_record(r_e);

            Entities::TableEntity table(0,0,0);
            auto entity = table.clone();

            auto crud_r_t = crud_ptr->create_record(*entity, "bleh");
            auto crud_r_f = crud_ptr->create_record(*entity, "bleh");

            auto crud_r_e = crud_ptr->create_record(*entity, "bleh");

			THEN("table is svaed in the DB")
			{
                REQUIRE(crud_r_t.has_value() == true);
                REQUIRE(crud_r_f.has_value() == true);
                REQUIRE(crud_r_e.has_error() == true);

                REQUIRE(crud_r_t.value() == true);
                REQUIRE(crud_r_f.value() == false);
                REQUIRE(crud_r_e.error() == error_msg);
			}
		}
	}

    GIVEN("no mock result provided for crud create")
	{
		WHEN("create")
		{
            Entities::TableEntity table(0,0,0);
            auto entity = table.clone();

            auto crud_r_t = crud_ptr->create_record(*entity, "bleh");

			THEN("error is returned")
			{
                REQUIRE(crud_r_t.has_error() == true);
			}
		}
	}

    GIVEN("mock result provided for crud read")
	{
        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        int items_size = 3;

        for (int i = 0; i < items_size; i++)
        {
            items.push_back(std::make_unique<Entities::TableEntity>(Entities::TableEntity(i, i, i)));
        }

        const auto r = cpp::result<bool, std::string> {true};
        crud_ptr->mock_read_records(r, items);

		WHEN("read")
		{
            std::vector<std::unique_ptr<Entities::BaseEntity>> read_items;
            Entities::TableEntity table(1, 1, 1);
            auto read_r = crud_ptr->read_records(read_items, table, "nah", Entities::TableEntity::match_any);

			THEN("table is saved in the DB")
			{
                REQUIRE(read_r.has_value() == true);
                REQUIRE(read_r.value() == true);
                REQUIRE(items.size() == read_items.size());

                for (int i = 0; i < items_size; i++)
                {
                    auto item = std::move(items.back());
                    items.pop_back();

                    auto item_read = std::move(read_items.back());
                    read_items.pop_back();

                    auto item_s = dynamic_cast<Entities::TableEntity*>(item.get());
                    auto item_r = dynamic_cast<Entities::TableEntity*>(item.get());
                    REQUIRE(item_s != nullptr);
                    REQUIRE(item_r != nullptr);
                    REQUIRE((*item_s) == (*item_r));
                }
			}
		}
	}

        GIVEN("mock result provided for crud read all")
	{
        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        int items_size = 3;

        for (int i = 0; i < items_size; i++)
        {
            items.push_back(std::make_unique<Entities::TableEntity>(Entities::TableEntity(i, i, i)));
        }

        const auto r = cpp::result<bool, std::string> {true};
        crud_ptr->mock_read_all_records(r, items);

		WHEN("read")
		{
            std::vector<std::unique_ptr<Entities::BaseEntity>> read_items;
            Entities::TableEntity table(1, 1, 1);
            auto read_r = crud_ptr->read_all_records(read_items, table, "nah", Entities::TableEntity::match_any);

			THEN("table is saved in the DB")
			{
                REQUIRE(read_r.has_value() == true);
                REQUIRE(read_r.value() == true);
                REQUIRE(items.size() == read_items.size());

                for (int i = 0; i < items_size; i++)
                {
                    auto item = std::move(items.back());
                    items.pop_back();

                    auto item_read = std::move(read_items.back());
                    read_items.pop_back();

                    auto item_s = dynamic_cast<Entities::TableEntity*>(item.get());
                    auto item_r = dynamic_cast<Entities::TableEntity*>(item.get());
                    REQUIRE(item_s != nullptr);
                    REQUIRE(item_r != nullptr);
                    REQUIRE((*item_s) == (*item_r));
                }
			}
		}
	}


    GIVEN("mock result provided for crud delete")
	{
        auto result = GENERATE
        (
            as<cpp::result<bool, std::string>>{},
            cpp::result<bool, std::string>{true},
            cpp::result<bool, std::string>{false}
        );

		WHEN("create")
		{
            auto r = std::move(result);
            crud_ptr->mock_delete_record(r);

            Entities::TableEntity table(0,0,0);
            auto entity = table.clone();

            auto crud_r = crud_ptr->delete_record(table, "bleh", Entities::TableEntity::match_any);

			THEN("table is svaed in the DB")
			{
                REQUIRE(r.has_value() == crud_r.has_value());
                REQUIRE(r.value() == crud_r.value());
			}
		}
	}
}