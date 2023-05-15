#include "Base.hpp"
#include "csv_helper.hpp"
#include <fstream>
#include <time.h>

namespace DateBase
{
    static const std::string TABLE_LAYOUT_PATH = "table_layout/table_layout.csv";
    static const std::string RESERVATIONS_PATH = "reservations/";


    auto create_table(std::unique_ptr<Entities::BaseEntity> &t, std::unique_ptr<DbConnector> &db) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table = dynamic_cast<Entities::TableEntity *>(t.get());

        if (table == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.\n");
        }

        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(0, 0, 0);
        std::vector<std::unique_ptr<Entities::BaseEntity>> tables;
        auto r_path = db.get()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        auto r_all = read_all_tables(tables, db);

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
            if (
                item->id == table->id
                || (item->x == table->x && item->y == table->y))
            {
                return cpp::fail("Table already exists\n");
            }
        }

        return csv_helper::create_record(t, filename);
    }

    auto read_tables(std::vector<std::unique_ptr<Entities::BaseEntity>> tables, std::unique_ptr<DbConnector> &db) noexcept -> cpp::result<bool, std::string>
    {
        // Entities::TableEntity *table = dynamic_cast<Entities::TableEntity*>(table.get());

        // if (table == nullptr)
        // {
        // 	return cpp::fail("Entity not of type Entities::TableEntity.\n");
        // }

        auto r_path = db.get()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();
        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(Entities::TableEntity(0, 0, 0));

        return csv_helper::read_records(tables, type, filename, Entities::TableEntity::db_match_record_by_id);
    }

    auto read_tables_by_x_y(std::vector<std::unique_ptr<Entities::BaseEntity>> tables, std::unique_ptr<DbConnector> &db) noexcept -> cpp::result<bool, std::string>
    {
        // Entities::TableEntity *table = dynamic_cast<Entities::TableEntity*>(table.get());

        // if (table == nullptr)
        // {
        // 	return cpp::fail("Entity not of type Entities::TableEntity.\n");
        // }

        auto r_path = db.get()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();
        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(Entities::TableEntity(0, 0, 0));

        return csv_helper::read_records(tables, type, filename, Entities::TableEntity::db_match_record_by_x_and_y);
    }

    auto read_all_tables(std::vector<std::unique_ptr<Entities::BaseEntity>> tables, std::unique_ptr<DbConnector> &db) noexcept -> cpp::result<bool, std::string>
    {
        auto r_path = db.get()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(Entities::TableEntity(0, 0, 0));

        return csv_helper::read_all_records(tables, type, filename, Entities::TableEntity::db_match_any);
    }

    auto update_table(std::unique_ptr<Entities::BaseEntity> &table, std::unique_ptr<DbConnector> &db) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table = dynamic_cast<Entities::TableEntity *>(table.get());

        if (table == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.\n");
        }

        auto r_path = db.get()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        return csv_helper::update_record(table, filename, Entities::TableEntity::db_match_record_by_id);
    }

    auto delete_table(std::unique_ptr<Entities::BaseEntity> &table, std::unique_ptr<DbConnector> &db) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table = dynamic_cast<Entities::TableEntity *>(table.get());

        if (table == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.\n");
        }

        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(0, 0, 0);
        std::vector<std::unique_ptr<Entities::BaseEntity>> tables;

        auto r_path = db.get()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        return csv_helper::delete_record(table, filename, Entities::TableEntity::db_match_record_by_id);
    }
}
