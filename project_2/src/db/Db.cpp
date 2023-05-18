#include <fstream>
#include <time.h>

#include "Base.hpp"
#include "Entities.hpp"
#include "DbConnector.hpp"
#include "csv_helper.hpp"

namespace DataBase
{
    auto read_tables_by_x_y(std::vector<std::unique_ptr<Entities::BaseEntity>> tables) noexcept -> cpp::result<bool, std::string>
    {
        // Entities::TableEntity *table = dynamic_cast<Entities::TableEntity*>(table.get());

        // if (table == nullptr)
        // {
        // 	return cpp::fail("Entity not of type Entities::TableEntity.\n");
        // }

        auto r_path = DbConnector::instance()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();
        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(Entities::TableEntity(0, 0, 0));

        return csv_helper::read_records(tables, type, filename, Entities::TableEntity::db_match_record_by_x_and_y);
    }

    auto read_all_tables(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables) noexcept -> cpp::result<bool, std::string>
    {
        auto r_path = DbConnector::instance()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(Entities::TableEntity(0, 0, 0));

        auto r_read_all = csv_helper::read_all_records(tables, type, filename, Entities::TableEntity::db_match_any);

        if(r_read_all.has_error())
        {
            return cpp::fail(r_read_all.error());
        }

        return r_read_all.value();
    }

    auto create_table(std::unique_ptr<Entities::BaseEntity> &t) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table = dynamic_cast<Entities::TableEntity *>(t.get());

        if (table == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.\n");
        }


        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(0, 0, 0);
        std::vector<std::unique_ptr<Entities::BaseEntity>> tables;

        auto r_path = DbConnector::instance()->get_table_layout_path();

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
            if (
                item->id == table->id
                || (item->x == table->x && item->y == table->y)
            )
            {
                return cpp::fail("Table already exists\n");
            }
        }

        return csv_helper::create_record(t, filename);
    }

    auto read_tables(std::vector<std::unique_ptr<Entities::BaseEntity>> tables) noexcept -> cpp::result<bool, std::string>
    {
        // Entities::TableEntity *table = dynamic_cast<Entities::TableEntity*>(table.get());

        // if (table == nullptr)
        // {
        // 	return cpp::fail("Entity not of type Entities::TableEntity.\n");
        // }

        auto r_path = DbConnector::instance()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();
        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(Entities::TableEntity(0, 0, 0));

        return csv_helper::read_records(tables, type, filename, Entities::TableEntity::db_match_record_by_id);
    }


    auto update_table(std::unique_ptr<Entities::BaseEntity> &table) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_ptr = dynamic_cast<Entities::TableEntity *>(table.get());

        if (table_ptr == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.\n");
        }

        auto r_path = DbConnector::instance()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        return csv_helper::update_record(table, filename, Entities::TableEntity::db_match_record_by_id);
    }

    auto delete_table(std::unique_ptr<Entities::BaseEntity> &table) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_ptr = dynamic_cast<Entities::TableEntity *>(table.get());

        if (table_ptr == nullptr)
        {
            return cpp::fail("Entity not of type Entities::TableEntity.\n");
        }

        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(0, 0, 0);
        std::vector<std::unique_ptr<Entities::BaseEntity>> tables;

        auto r_path = DbConnector::instance()->get_table_layout_path();

        if (r_path.has_error())
        {
            return cpp::fail(r_path.error());
        }

        std::string filename = r_path.value();

        return csv_helper::delete_record(table, filename, Entities::TableEntity::db_match_record_by_id);
    }
}
