#include "TableEntity.hpp"
#include "Base.hpp"
#include "conversion_helper.hpp"

namespace Entities
{
    TableEntity::TableEntity(int x, int y, unsigned int capacity)
    {
        this->id = create_new_uuid();
        this->x = x;
        this->y = y;
        this->capacity = capacity;
    }

    TableEntity::~TableEntity()
    {
    }

    std::string TableEntity::parse_to_csv()
    {
        return BaseEntity::parse_to_csv()+ this->delimiter + std::to_string(this->x) + this->delimiter + std::to_string(this->y) + this->delimiter + std::to_string(this->capacity);
    }

    int TableEntity::get_persitable_prop_count()
    {
        return this->persitable_prop_count + BaseEntity::get_persitable_prop_count();
    }

    auto TableEntity::parse_from_csv(std::unique_ptr<BaseEntity> &target, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string>
    {
        if (fields.size() < index + this->get_persitable_prop_count())
        {
            return cpp::fail("Not enough arguments.\n");
        }

        // convert data
        auto id = Helper::str_to_uuid(fields.at(index));
        auto x = Helper::str_to_int_strict(fields.at(index + 1));
        auto y = Helper::str_to_int_strict(fields.at(index + 2));
        auto capacity = Helper::str_to_int_strict(fields.at(index + 3));

        if (id.has_error() || x.has_error() || y.has_error() || capacity.has_error())
        {
            return cpp::fail("Could not parse all arguments.\n");
        }

        std::unique_ptr<BaseEntity> table = std::make_unique<TableEntity>(TableEntity(x.value(), y.value(), capacity.value()));
        table.get()->id = id.value();

        target.swap(table);
        index += get_persitable_prop_count();

        return true;
    }

    auto TableEntity::match_by_id(std::unique_ptr<BaseEntity> &target, std::unique_ptr<BaseEntity> &source) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_source = dynamic_cast<Entities::TableEntity *>(source.get());

        if (table_source == nullptr)
        {
            return cpp::fail("Source not of type Entities::TableEntity.\n");
        }

        Entities::TableEntity *table_target = dynamic_cast<Entities::TableEntity *>(target.get());

        if (table_target == nullptr)
        {
            return cpp::fail("Target not of type Entities::TableEntity.\n");
        }

        return table_source->id == table_target->id;
    }

    auto TableEntity::match_any(std::unique_ptr<BaseEntity> &target, std::unique_ptr<BaseEntity> &source) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_source = dynamic_cast<Entities::TableEntity *>(source.get());

        if (table_source == nullptr)
        {
            return cpp::fail("Source not of type Entities::TableEntity.\n");
        }

        Entities::TableEntity *table_target = dynamic_cast<Entities::TableEntity *>(target.get());

        if (table_target == nullptr)
        {
            return cpp::fail("Target not of type Entities::TableEntity.\n");
        }

        return true;
    }

    auto TableEntity::match_by_x_and_y(std::unique_ptr<BaseEntity> &target, std::unique_ptr<BaseEntity> &source) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity *table_source = dynamic_cast<Entities::TableEntity *>(source.get());

        if (table_source == nullptr)
        {
            return cpp::fail("Source not of type Entities::TableEntity.\n");
        }

        Entities::TableEntity *table_target = dynamic_cast<Entities::TableEntity *>(target.get());

        if (table_target == nullptr)
        {
            return cpp::fail("Target not of type Entities::TableEntity.\n");
        }

        return table_source->x == table_target->x && table_source->y == table_target->y;
    }
}

