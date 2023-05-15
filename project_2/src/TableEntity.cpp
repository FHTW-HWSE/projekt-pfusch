#include "TableEntity.hpp"
#include "Base.hpp"
#include "sting_conversion_helper.hpp"

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
        return BaseEntity::parse_to_csv() + std::to_string(this->x) + this->delimiter + std::to_string(this->y) + this->delimiter + std::to_string(this->capacity);
    }

    int TableEntity::get_persitable_prop_count()
    {
        return this->persitable_prop_count + BaseEntity::get_persitable_prop_count();
    }

    bool TableEntity::equals(const BaseEntity &target)
    {

        const TableEntity *tmp = dynamic_cast<const TableEntity *>(&target);

        return 
            tmp != nullptr 
            && this->id == tmp->id 
            && this->x == tmp->x 
            && this->y == tmp->y 
            && this->capacity == tmp->capacity;
    }

    bool TableEntity::equals(const std::unique_ptr<BaseEntity> &target)
    {
        const TableEntity *tmp = dynamic_cast<const TableEntity *>(target.get());
        return tmp != nullptr && equals(*tmp);
    }

    auto TableEntity::db_read_record(std::unique_ptr<BaseEntity> &target, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string>
    {
        if (fields.size() < index + this->get_persitable_prop_count())
        {
            return cpp::fail("Not enough arguments.\n");
        }

        // convert data
        auto id = str_to_uuid(fields.at(index));
        auto x = str_to_int_strict(fields.at(index + 1));
        auto y = str_to_int_strict(fields.at(index + 2));
        auto capacity = str_to_int_strict(fields.at(index + 3));

        if (id.has_error() || x.has_error() || y.has_error() || capacity.has_error())
        {
            return cpp::fail("Could not parse all arguments.\n");
        }

        std::unique_ptr<BaseEntity> table = std::make_unique<BaseEntity>(TableEntity(x.value(), y.value(), capacity.value()));
        table.get()->id = id.value();

        target.swap(table);
        index += get_persitable_prop_count();

        return true;
    }

    auto TableEntity::db_write_record() noexcept -> cpp::result<std::string, std::string>
    {
        return this->parse_to_csv();
    }

    auto TableEntity::db_match_record_by_id(std::unique_ptr<BaseEntity> &source, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string>
    {
        if (fields.size() < index + source->get_persitable_prop_count())
        {
            return cpp::fail("Not enough arguments.\n");
        }

        auto id = str_to_uuid(fields.at(index));

        if (id.has_error())
        {
            return cpp::fail("Could not parse id.\n");
        }

        return source.get()->id == id.value();
    }

    auto TableEntity::db_match_any(std::unique_ptr<BaseEntity> &source, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string>
    {
        if (fields.size() < index + persitable_prop_count)
        {
            return cpp::fail("Not enough arguments.\n");
        }

        // convert data
        auto id = str_to_uuid(fields.at(index));
        auto x = str_to_int_strict(fields.at(index + 1));
        auto y = str_to_int_strict(fields.at(index + 2));
        auto capacity = str_to_int_strict(fields.at(index + 3));

        if (id.has_error() || x.has_error() || y.has_error() || capacity.has_error())
        {
            return cpp::fail("Could not parse all arguments.\n");
        }

        std::unique_ptr<BaseEntity> table = std::make_unique<BaseEntity>(TableEntity(x.value(), y.value(), capacity.value()));
        table.get()->id = id.value();

        source.swap(table);
        index += persitable_prop_count;

        return true;
    }

    auto TableEntity::db_match_record_by_x_and_y(std::unique_ptr<BaseEntity> &source, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string>
    {
        if (fields.size() < index + persitable_prop_count)
        {
            return cpp::fail("Not enough arguments.\n");
        }

        const TableEntity *table = dynamic_cast<const TableEntity *>(source.get());

        if (table == nullptr)
        {
            return cpp::fail("Entity is not of type TableEntity\n");
        }

        auto x = str_to_int_strict(fields.at(index + 1));
        auto y = str_to_int_strict(fields.at(index + 2));

        if (x.has_error())
        {
            // std::strerror(errno)
            return cpp::fail(std::strerror(static_cast<int>(x.error())));
        }

        if (y.has_error())
        {
            // std::strerror(errno)
            return cpp::fail(std::strerror(static_cast<int>(y.error())));
        }

        return table->x == x.value() && table->y == y.value();
    }
}

