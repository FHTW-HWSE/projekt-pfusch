#include <fstream>
#include <time.h>

#include "Base.hpp"
#include "Entities.hpp"
#include "Query.hpp"
#include "Enviroment.hpp"

namespace DataBase
{
    auto Query::read_tables_by_x_y(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables, std::unique_ptr<Entities::BaseEntity> &table) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_ptr = dynamic_cast<Entities::TableEntity *>(table.get());

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

        std::unique_ptr<Entities::BaseEntity> type = std::make_unique<Entities::TableEntity>(Entities::TableEntity(0, 0, 0));

        auto r_read_all = Enviroment::Config::instance()->get_db_con()->get_crud()->read_all_records(tables, type, filename, Entities::TableEntity::match_any);

        if(r_read_all.has_error())
        {
            return cpp::fail(r_read_all.error());
        }

        return r_read_all.value();
    }

    auto Query::create_table(std::unique_ptr<Entities::BaseEntity> &t) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table = dynamic_cast<Entities::TableEntity *>(t.get());

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

    auto Query::read_tables_by_id(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables, std::unique_ptr<Entities::BaseEntity> &table) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_ptr = dynamic_cast<Entities::TableEntity *>(table.get());

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

    auto Query::update_table(std::unique_ptr<Entities::BaseEntity> &table) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_ptr = dynamic_cast<Entities::TableEntity *>(table.get());

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

    auto Query::delete_table(std::unique_ptr<Entities::BaseEntity> &table) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_ptr = dynamic_cast<Entities::TableEntity *>(table.get());

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
}
