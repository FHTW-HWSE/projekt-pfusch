#include "DbFascade.hpp"
#include "Base.hpp"
#include "TableEntity.hpp"
#include "Query.hpp"

namespace Fascades
{
    auto DbFascade::fill_tables_vector(std::vector<std::unique_ptr<Entities::TableEntity>> &tables, std::vector<std::unique_ptr<Entities::BaseEntity>> &items) noexcept -> cpp::result<bool, std::string>
    {
        for (const auto &s : items)
        {
            auto t_ptr = dynamic_cast<Entities::TableEntity*>(s.get());

            if(t_ptr == nullptr)
            {
                return cpp::fail("Read something else than a Table from DB.");
            }

            auto unique_table = std::make_unique<Entities::TableEntity>(*t_ptr);
            tables.push_back(std::move(unique_table));
        }

        return true;
    }

    auto DbFascade::get_tables_by_x_y(std::vector<std::unique_ptr<Entities::TableEntity>> &tables, const int &x, const int &y) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity table(x, y, 0);

        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        auto query_result = DataBase::Query::read_tables_by_x_y(items, table);

        if(query_result.has_error()){
            return query_result;
        }

        auto fill_r = fill_tables_vector(tables, items);

        if(fill_r.has_error())
        {
            return fill_r;
        }

        return items.size() > 0;
    }

    auto DbFascade::get_tables_by_id(std::vector<std::unique_ptr<Entities::TableEntity>> &tables, const uuids::uuid &id) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity table(0, 0, 0);
        table.id = id;

        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        auto query_result = DataBase::Query::read_tables_by_id(items, table);

        if(query_result.has_error()){
            return query_result;
        }

        auto fill_r = fill_tables_vector(tables, items);

        if(fill_r.has_error())
        {
            return fill_r;
        }

        return items.size() > 0;
    }

    auto DbFascade::get_all_tables(std::vector<std::unique_ptr<Entities::TableEntity>> &tables) noexcept -> cpp::result<bool, std::string>
    {
        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        auto query_result = DataBase::Query::read_all_tables(items);

        if(query_result.has_error()){
            return query_result;
        }

        auto fill_r = fill_tables_vector(tables, items);

        if(fill_r.has_error())
        {
            return fill_r;
        }

        return items.size() > 0;
    }

    auto DbFascade::create_table(Entities::TableEntity &table) noexcept -> cpp::result<bool, std::string>
    {
        return DataBase::Query::create_table(table);
    }

    auto DbFascade::update_table(Entities::TableEntity &table) noexcept -> cpp::result<bool, std::string>
    {
        return DataBase::Query::update_table(table);
    }

    auto DbFascade::delete_table(Entities::TableEntity &table) noexcept -> cpp::result<bool, std::string>
    {
        return DataBase::Query::delete_table(table);
    }
}