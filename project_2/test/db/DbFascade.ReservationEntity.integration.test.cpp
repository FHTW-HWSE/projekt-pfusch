#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <string>

#include "MainTest.hpp"
#include "test.hpp"
#include "Enviroment.hpp"
#include "TableEntity.hpp"
#include "DbFascade.hpp"

SCENARIO("DbFascade ReservationEntity")
{
    Enviroment_actual();

	GIVEN("want to save reservation")
	{
        clear_db();

		auto reservation = GENERATE_COPY
        (
            as<Entities::ReservationEntity>{},
			Entities::ReservationEntity(Entities::TableEntity(0,0,0), 0, 0, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(2,2,2), 2, 2, "contact")
		);

		WHEN("saves reservation")
		{

            auto r_create = Fascades::DbFascade::create_reservation(reservation);

            std::vector<std::unique_ptr<Entities::ReservationEntity>> reservations;
            auto r_read = Fascades::DbFascade::get_reservations_by_id(reservations, reservation.id);

			THEN("table is svaed in the DB")
			{
				REQUIRE(r_create.has_value() == true);
				REQUIRE(r_create.value() == true);

				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == true);

				REQUIRE(reservations.size() == 1);

				const auto &table_1 = reservations.back();

				REQUIRE(reservation == *table_1);
			}
		}

        clear_db();
	}

	GIVEN("open reservation for the table alrady exists")
	{
        clear_db();

		auto reservation = GENERATE_COPY
        (
            as<Entities::ReservationEntity>{},
			Entities::ReservationEntity(Entities::TableEntity(0,0,0), 0, 0, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 0, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(2,2,2), 2, 0, "contact")
		);

		WHEN("save a new open reservation for the same table")
		{

            auto r_create1 = Fascades::DbFascade::create_reservation(reservation);

			reservation.id = reservation.create_new_uuid();

            auto r_create2 = Fascades::DbFascade::create_reservation(reservation);

			THEN("table is not saved in DB")
			{
				REQUIRE(r_create1.has_value() == true);
				REQUIRE(r_create1.value() == true);
				REQUIRE(r_create2.has_error() == true);
			}
		}

        clear_db();
	}

	GIVEN("want to get reservation by x y")
	{
        clear_db();

		auto reservation = GENERATE_COPY
        (
            as<Entities::ReservationEntity>{},
			Entities::ReservationEntity(Entities::TableEntity(0,0,0), 0, 0, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(2,2,2), 2, 2, "contact")
		);

		WHEN("gets reservation")
		{

            auto r_create = Fascades::DbFascade::create_reservation(reservation);

            std::vector<std::unique_ptr<Entities::ReservationEntity>> reservations;
            auto r_read = Fascades::DbFascade::get_reservations_by_id(reservations, reservation.id);

			THEN("table is read from DB")
			{
				REQUIRE(r_create.has_value() == true);
				REQUIRE(r_create.value() == true);

				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == true);

				REQUIRE(reservations.size() == 1);

				const auto &table_1 = reservations.back();

				REQUIRE(reservation == *table_1);
			}
		}

        clear_db();
	}

	GIVEN("want to get reservation by x y")
	{
        clear_db();

		auto reservation = GENERATE_COPY
        (
            as<Entities::ReservationEntity>{},
			Entities::ReservationEntity(Entities::TableEntity(0,0,0), 0, 0, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(2,2,2), 2, 2, "contact")
		);

		WHEN("gets reservation")
		{

            auto r_create = Fascades::DbFascade::create_reservation(reservation);

            std::vector<std::unique_ptr<Entities::ReservationEntity>> reservations;
            auto r_read = Fascades::DbFascade::get_reservations_by_x_y(reservations, reservation.table.get()->x, reservation.table.get()->y);

			THEN("table read from DB")
			{
				REQUIRE(r_create.has_value() == true);
				REQUIRE(r_create.value() == true);

				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == true);

				REQUIRE(reservations.size() == 1);

				const auto &table_1 = reservations.back();

				REQUIRE(reservation == *table_1);
			}
		}

        clear_db();
	}

	GIVEN("want to get reservations by x y")
	{
        clear_db();

		std::vector<Entities::ReservationEntity> source;


		source.push_back(Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"));
		source.push_back(Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"));
		source.push_back(Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"));
		source.push_back(Entities::ReservationEntity(Entities::TableEntity(2,2,2), 2, 2, "contact"));
		source.push_back(Entities::ReservationEntity(Entities::TableEntity(0,0,0), 0, 0, "contact"));

		WHEN("gets reservations")
		{

			for (auto &res : source)
			{
            	auto r_create = Fascades::DbFascade::create_reservation(res);
			}

            std::vector<std::unique_ptr<Entities::ReservationEntity>> reservations;
            auto r_read = Fascades::DbFascade::get_reservations_by_x_y(reservations, 1, 1);

			THEN("tables are read from DB")
			{
				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == true);
				REQUIRE(reservations.size() == 3);

				source.pop_back();
				source.pop_back();

				while (reservations.empty() == false)
				{
					const auto &table_1 = reservations.back();
					const auto &table_2 = source.back();  
					
					REQUIRE(table_2 == *table_1);

					reservations.pop_back();
					source.pop_back();
				}
			}
		}

        clear_db();
	}

	GIVEN("want to get open reservations")
	{
        clear_db();

		std::vector<Entities::ReservationEntity> source;


		source.push_back(Entities::ReservationEntity(Entities::TableEntity(0,0,0), 0, 0, "contact"));
		source.push_back(Entities::ReservationEntity(Entities::TableEntity(1,1,0), 1, 0, "contact"));
		source.push_back(Entities::ReservationEntity(Entities::TableEntity(2,2,0), 2, 0, "contact"));
		source.push_back(Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"));
		source.push_back(Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"));

		WHEN("gets open reservations")
		{

			for (auto &res : source)
			{
            	auto r_create = Fascades::DbFascade::create_reservation(res);
			}

            std::vector<std::unique_ptr<Entities::ReservationEntity>> reservations;
            auto r_read = Fascades::DbFascade::get_all_open_reservations(reservations);

			THEN("tables are read from DB")
			{
				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == true);

				REQUIRE(reservations.size() == 3);

				source.pop_back();
				source.pop_back();

				while (reservations.empty() == false)
				{
					const auto &table_1 = reservations.back();
					const auto &table_2 = source.back();  
					
					REQUIRE(table_2 == *table_1);

					reservations.pop_back();
					source.pop_back();
				}
			}
		}

        clear_db();
	}

	GIVEN("want to get update a reservation")
	{
        clear_db();

		auto reservation = GENERATE_COPY
        (
            as<Entities::ReservationEntity>{},
			Entities::ReservationEntity(Entities::TableEntity(0,0,0), 0, 0, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(2,2,2), 2, 2, "contact")
		);

		WHEN("update reservation")
		{

            auto r_create = Fascades::DbFascade::create_reservation(reservation);

            auto r_update = Fascades::DbFascade::update_reservation(reservation);

            std::vector<std::unique_ptr<Entities::ReservationEntity>> reservations;
			auto r_read = Fascades::DbFascade::get_reservations_by_id(reservations, reservation.id);

			THEN("reservation is updated in DB")
			{
				REQUIRE(r_create.has_value() == true);
				REQUIRE(r_create.value() == true);

				REQUIRE(r_update.has_value() == true);
				REQUIRE(r_update.value() == true);

				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == true);

				REQUIRE(reservations.size() == 1);

				const auto &table_1 = reservations.back();

				REQUIRE(reservation == *table_1);
			}
		}

        clear_db();
	}

	GIVEN("want to get update a reservation but it does not exist in DB")
	{
        clear_db();

		auto reservation = GENERATE_COPY
        (
            as<Entities::ReservationEntity>{},
			Entities::ReservationEntity(Entities::TableEntity(0,0,0), 0, 0, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(2,2,2), 2, 2, "contact")
		);

		WHEN("update reservation")
		{

            auto r_update = Fascades::DbFascade::update_reservation(reservation);

			THEN("reservation is updated in DB")
			{
				REQUIRE(r_update.has_value() == true);
				REQUIRE(r_update.value() == false);
			}
		}

        clear_db();
	}

	GIVEN("want to get delete a reservation")
	{
        clear_db();

		auto reservation = GENERATE_COPY
        (
            as<Entities::ReservationEntity>{},
			Entities::ReservationEntity(Entities::TableEntity(0,0,0), 0, 0, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(2,2,2), 2, 2, "contact")
		);

		WHEN("delete reservation")
		{

            auto r_create = Fascades::DbFascade::create_reservation(reservation);

            auto r_delete = Fascades::DbFascade::delete_reservation(reservation);

            std::vector<std::unique_ptr<Entities::ReservationEntity>> reservations;
			auto r_read = Fascades::DbFascade::get_reservations_by_id(reservations, reservation.id);

			THEN("reservation is updated in DB")
			{
				REQUIRE(r_create.has_value() == true);
				REQUIRE(r_create.value() == true);

				REQUIRE(r_delete.has_value() == true);
				REQUIRE(r_delete.value() == true);

				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == false);

				REQUIRE(reservations.size() == 0);
			}
		}

        clear_db();
	}

	GIVEN("want to get delete a reservation but it does not exist in DB")
	{
        clear_db();

		auto reservation = GENERATE_COPY
        (
            as<Entities::ReservationEntity>{},
			Entities::ReservationEntity(Entities::TableEntity(0,0,0), 0, 0, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"),
			Entities::ReservationEntity(Entities::TableEntity(2,2,2), 2, 2, "contact")
		);

		WHEN("delete reservation")
		{

            auto r_delete = Fascades::DbFascade::delete_reservation(reservation);

			std::vector<std::unique_ptr<Entities::ReservationEntity>> reservations;
			auto r_read = Fascades::DbFascade::get_reservations_by_id(reservations, reservation.id);


			THEN("no reservation is deleted")
			{
				REQUIRE(r_delete.has_value() == true);
				REQUIRE(r_delete.value() == false);

				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == false);

				REQUIRE(reservations.size() == 0);
			}
		}

        clear_db();
	}

	GIVEN("want to get delete a reservation with other reservations already in DB")
	{
        clear_db();

		std::vector<Entities::ReservationEntity> source;


		source.push_back(Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"));
		source.push_back(Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"));
		source.push_back(Entities::ReservationEntity(Entities::TableEntity(1,1,1), 1, 1, "contact"));
		source.push_back(Entities::ReservationEntity(Entities::TableEntity(2,2,2), 2, 2, "contact"));
		source.push_back(Entities::ReservationEntity(Entities::TableEntity(0,0,0), 0, 0, "contact"));

		WHEN("gets reservations")
		{

			for (auto &res : source)
			{
            	auto r_create = Fascades::DbFascade::create_reservation(res);
			}

			auto &res = source.back();

			auto r_delete = Fascades::DbFascade::delete_reservation(res);

            std::vector<std::unique_ptr<Entities::ReservationEntity>> reservations;
            auto r_read = Fascades::DbFascade::get_all_reservations(reservations);

			THEN("tables are read from DB")
			{
				REQUIRE(r_delete.has_value() == true);
				REQUIRE(r_delete.value() == true);

				REQUIRE(r_read.has_value() == true);
				REQUIRE(r_read.value() == true);
				REQUIRE(reservations.size() == 4);

				source.pop_back();

				while (reservations.empty() == false)
				{
					const auto &table_1 = reservations.back();
					const auto &table_2 = source.back();  
					
					REQUIRE(table_2 == *table_1);

					reservations.pop_back();
					source.pop_back();
				}
			}
		}
	}

	Enviroment_mock();
}