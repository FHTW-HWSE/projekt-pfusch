#include <fstream>
#include <time.h>

#include "Base.hpp"
#include "Entities.hpp"
#include "Query.hpp"
#include "Enviroment.hpp"

namespace DataBase
{
#pragma region TableEntity
    auto Query::read_tables_by_x_y(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables, Entities::BaseEntity &table) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_ptr = dynamic_cast<Entities::TableEntity *>(&table);

        if (table_ptr == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.");
        }

        auto r_path = Enviroment::Config::instance()->get_db_con()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        return Enviroment::Config::instance()->get_db_con()->get_crud()->read_records(tables, table, filename, Entities::TableEntity::match_by_x_and_y);
    }

    auto Query::read_all_tables(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables) noexcept -> cpp::result<bool, std::string>
    {
        auto r_path = Enviroment::Config::instance()->get_db_con()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        Entities::TableEntity type(1, 1, 1);

        auto r_read_all = Enviroment::Config::instance()->get_db_con()->get_crud()->read_all_records(tables, type, filename, Entities::TableEntity::match_any);

        if(r_read_all.has_error())
        {
            return cpp::fail(r_read_all.error());
        }

        return r_read_all.value();
    }

    auto Query::create_table(Entities::BaseEntity &t) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table = dynamic_cast<Entities::TableEntity *>(&t);

        if (table == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.");
        }

        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(0, 0, 0);
        std::vector<std::unique_ptr<Entities::BaseEntity>> tables;

        auto r_path = Enviroment::Config::instance()->get_db_con()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        auto r_all = read_all_tables(tables);

        if (r_all.has_error())
        {
            return cpp::fail(r_all.error());
        }

        if (r_all.value() == false)
        {
            return false;
        }

        for (const auto &s : tables)
        {
            Entities::TableEntity *item = dynamic_cast<Entities::TableEntity *>(s.get());
            if 
            (
                item->id == table->id
                || (item->x == table->x && item->y == table->y)
            )
            {
                return cpp::fail("Table already exists");
            }
        }

        return Enviroment::Config::instance()->get_db_con()->get_crud()->create_record(t, filename);
    }

    auto Query::read_tables_by_id(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables, Entities::BaseEntity &table) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_ptr = dynamic_cast<Entities::TableEntity *>(&table);

        if (table_ptr == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.");
        }

        auto r_path =Enviroment::Config::instance()->get_db_con()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();
        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(Entities::TableEntity(0, 0, 0));

        return Enviroment::Config::instance()->get_db_con()->get_crud()->read_records(tables, table, filename, Entities::TableEntity::match_by_id);
    }

    auto Query::update_table(Entities::BaseEntity &table) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_ptr = dynamic_cast<Entities::TableEntity *>(&table);

        if (table_ptr == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.");
        }

        auto r_path = Enviroment::Config::instance()->get_db_con()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        return Enviroment::Config::instance()->get_db_con()->get_crud()->update_record(table, filename, Entities::TableEntity::match_by_id);
    }

    auto Query::delete_table(Entities::BaseEntity &table) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_ptr = dynamic_cast<Entities::TableEntity *>(&table);

        if (table_ptr == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.");
        }

        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(0, 0, 0);
        std::vector<std::unique_ptr<Entities::BaseEntity>> tables;

        auto r_path = Enviroment::Config::instance()->get_db_con()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        return Enviroment::Config::instance()->get_db_con()->get_crud()->delete_record(table, filename, Entities::TableEntity::match_by_id);
    }

#pragma endregion

    auto Query::create_reservation(Entities::BaseEntity &t) noexcept -> cpp::result<bool, std::string>
    {
        Entities::ReservationEntity *res = dynamic_cast<Entities::ReservationEntity *>(&t);

        if (res == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.");
        }

        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::ReservationEntity>();
        std::vector<std::unique_ptr<Entities::BaseEntity>> reservations;

        auto r_path = Enviroment::Config::instance()->get_db_con()->get_reservation_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        auto r_all = read_all_reservations(reservations);

        if (r_all.has_error())
        {
            return cpp::fail(r_all.error());
        }

        if (r_all.value() == false)
        {
            return false;
        }

        for (const auto &s : reservations)
        {
            Entities::ReservationEntity *item = dynamic_cast<Entities::ReservationEntity *>(s.get());

            if 
            (
                item->id == res->id
                || (
                    item->table.get()->x == res->table.get()->x
                    && item->table.get()->y == res->table.get()->y
                    && item->end_time == 0
                )
            )
            {
                return cpp::fail("An open reservation for this table alreday exists.");
            }
        }

        return Enviroment::Config::instance()->get_db_con()->get_crud()->create_record(t, filename);
    }
    
    auto Query::read_reservations_by_x_y(std::vector<std::unique_ptr<Entities::BaseEntity>> &reservations, Entities::BaseEntity &reservation) noexcept -> cpp::result<bool, std::string>
    {
        Entities::ReservationEntity *table_ptr = dynamic_cast<Entities::ReservationEntity *>(&reservation);

        if (table_ptr == nullptr)
        {
            return cpp::fail("Entity not of type Entities::ReservationEntity.");
        }

        auto r_path = Enviroment::Config::instance()->get_db_con()->get_reservation_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        return Enviroment::Config::instance()->get_db_con()->get_crud()
            ->read_records(reservations, reservation, filename, Entities::ReservationEntity::match_by_table_x_y);
    }

    auto Query::read_reservations_by_id(std::vector<std::unique_ptr<Entities::BaseEntity>> &reservations, Entities::BaseEntity &reservation) noexcept -> cpp::result<bool, std::string>
    {
        Entities::ReservationEntity *table_ptr = dynamic_cast<Entities::ReservationEntity *>(&reservation);

        if (table_ptr == nullptr)
        {
            return cpp::fail("Entity not of type Entities::ReservationEntity.");
        }

        auto r_path =Enviroment::Config::instance()->get_db_con()->get_reservation_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();
        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::ReservationEntity>(Entities::ReservationEntity());

        return Enviroment::Config::instance()->get_db_con()->get_crud()
            ->read_records(reservations, reservation, filename, Entities::ReservationEntity::match_by_id);
    }

    auto Query::read_all_open_reservations(std::vector<std::unique_ptr<Entities::BaseEntity>> &reservations, Entities::BaseEntity &reservation) noexcept -> cpp::result<bool, std::string>
    {
        Entities::ReservationEntity *table_ptr = dynamic_cast<Entities::ReservationEntity *>(&reservation);

        if (table_ptr == nullptr)
        {
            return cpp::fail("Entity not of type Entities::ReservationEntity.");
        }

        auto r_path =Enviroment::Config::instance()->get_db_con()->get_reservation_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();
        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::ReservationEntity>(Entities::ReservationEntity());

        return Enviroment::Config::instance()->get_db_con()->get_crud()
            ->read_records(reservations, reservation, filename, Entities::ReservationEntity::match_open_reservation);
    }

    auto Query::read_all_reservations(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables) noexcept -> cpp::result<bool, std::string>
    {
        auto r_path = Enviroment::Config::instance()->get_db_con()->get_reservation_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        Entities::ReservationEntity type;

        auto r_read_all = Enviroment::Config::instance()->get_db_con()->get_crud()
            ->read_all_records(tables, type, filename, Entities::ReservationEntity::match_any);

        if(r_read_all.has_error())
        {
            return cpp::fail(r_read_all.error());
        }

        return r_read_all.value();
    }

    auto Query::update_reservation(Entities::BaseEntity &reservation) noexcept -> cpp::result<bool, std::string>
    {
        Entities::ReservationEntity *table_ptr = dynamic_cast<Entities::ReservationEntity *>(&reservation);

        if (table_ptr == nullptr)
        {
            return cpp::fail("Entity not of type Entities::ReservationEntity.");
        }

        auto r_path = Enviroment::Config::instance()->get_db_con()->get_reservation_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        return Enviroment::Config::instance()->get_db_con()->get_crud()->update_record(reservation, filename, Entities::ReservationEntity::match_by_id);
    }

    auto Query::delete_reservation(Entities::BaseEntity &reservation) noexcept -> cpp::result<bool, std::string>
    {
        Entities::ReservationEntity *table_ptr = dynamic_cast<Entities::ReservationEntity *>(&reservation);

        if (table_ptr == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.");
        }

        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::ReservationEntity>();
        std::vector<std::unique_ptr<Entities::BaseEntity>> tables;

        auto r_path = Enviroment::Config::instance()->get_db_con()->get_reservation_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        return Enviroment::Config::instance()->get_db_con()->get_crud()->delete_record(reservation, filename, Entities::ReservationEntity::match_by_id);
    }

}
