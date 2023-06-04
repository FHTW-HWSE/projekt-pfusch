#include "ReservationEntity.hpp"

namespace Entities
{
    ReservationEntity::ReservationEntity ( std::unique_ptr<Entities::TableEntity> &table, std::string &contact_person) : BaseEntity()
    {
        this->table = std::make_unique<TableEntity>(*table);
        this->contact_person = contact_person;
    }

    ReservationEntity::ReservationEntity(const ReservationEntity &reservation)
    {
        this->table = std::make_unique<TableEntity>(*reservation.table);
        this->contact_person = reservation.contact_person;
    }

    ReservationEntity::~ReservationEntity()
    {
    }

    std::unique_ptr<BaseEntity> ReservationEntity::clone() const
    {
        return std::make_unique<ReservationEntity>( *this );
    }

    bool ReservationEntity::isEqual(const BaseEntity& obj) const
    {
        // will never throw as isEqual is called only when
        // (typeid(lhs) == typeid(rhs)) is true.
        auto v = dynamic_cast<const ReservationEntity&>(obj); 
        
        return BaseEntity::isEqual(v) 
            && contact_person == v.contact_person;
    }

    std::string ReservationEntity::parse_to_csv()
    {
        return BaseEntity::parse_to_csv()
            + this->table.get()->parse_to_csv() 
            + this->delimiter + this->contact_person;
    }

    auto ReservationEntity::parse_from_csv(std::unique_ptr<BaseEntity> &target, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string>
    {
        if (fields.size() < index + this->get_persitable_prop_count())
        {
            return cpp::fail("Not enough arguments.\n");
        }

        // convert data
        // auto id = Helper::str_to_uuid(fields.at(index));
        // auto x = Helper::str_to_int_strict(fields.at(index + 1));
        // auto y = Helper::str_to_int_strict(fields.at(index + 2));
        // auto capacity = Helper::str_to_int_strict(fields.at(index + 3));

        // if (id.has_error() || x.has_error() || y.has_error() || capacity.has_error())
        // {
        //     return cpp::fail("Could not parse all arguments.\n");
        // }

        // std::unique_ptr<BaseEntity> table = std::make_unique<TableEntity>(TableEntity(x.value(), y.value(), capacity.value()));
        // table.get()->id = id.value();

        // target.swap(table);
        // index += get_persitable_prop_count();

        return cpp::fail("not implemented");

    }

    int ReservationEntity::get_persitable_prop_count()
    {
        return this->persitable_prop_count;
    }

}
