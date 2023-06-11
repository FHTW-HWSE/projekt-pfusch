#include "ReservationEntity.hpp"
#include "conversion_helper.hpp"

namespace Entities
{
    ReservationEntity::ReservationEntity() : BaseEntity()
    {
        this->table = std::make_unique<TableEntity>(TableEntity());
        this->start_time = 0;
        this->end_time = 0;
        this->contact_person = "default";
    }

    ReservationEntity::ReservationEntity( const Entities::TableEntity &table, const std::string &contact_person) : BaseEntity()
    {
        this->table = std::make_unique<TableEntity>(table);
        this->start_time = 0;
        this->end_time = 0;
        this->contact_person = contact_person;
    }

    ReservationEntity::ReservationEntity(const Entities::TableEntity &table, const  time_t &start_time, const time_t &end_time, const std::string &contact_person) : ReservationEntity(table, contact_person)
    {
        this->start_time = start_time;
        this->end_time = end_time;
    }


    ReservationEntity::ReservationEntity(const ReservationEntity &reservation) : BaseEntity(reservation)
    {
        this->table = std::make_unique<TableEntity>(*reservation.table);
        this->start_time = reservation.start_time;
        this->end_time = reservation.end_time;
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
            && (*this->table) == (*v.table)
            && this->start_time == v.start_time
            && this->end_time == v.end_time 
            && contact_person == v.contact_person;
    }

    std::string ReservationEntity::parse_to_csv()
    {
        return BaseEntity::parse_to_csv()
            + this->delimiter + this->table.get()->parse_to_csv() 
            + this->delimiter + Helper::time_t_to_string(this->start_time)
            + this->delimiter +  Helper::time_t_to_string(this->end_time)
            + this->delimiter + this->contact_person;
    }

    auto ReservationEntity::parse_from_csv(std::unique_ptr<BaseEntity> &target, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string>
    {
        if (fields.size() < (index + persitable_prop_count))
        {
            return cpp::fail("Not enough data in argument fields.");
        }

        // convert data
        auto id = Helper::str_to_uuid(fields.at(index++));

        auto id_str = Helper::id_to_string(id.value());

        if(id.has_error())
        {
            return cpp::fail("could not parse id.");
        }

        TableEntity tmp_table(0,0,0);
        std::unique_ptr<BaseEntity> parse_target(nullptr);
        auto parse_r = tmp_table.parse_from_csv(parse_target, fields, index);

        index++;
        
        if(parse_r.has_error())
        {
            return parse_r;
        }

        TableEntity *table_ptr = dynamic_cast<TableEntity*>(parse_target.get());

        if (table_ptr == nullptr)
        {
            return cpp::fail("Could not parse table from csv.");
        }

        auto start_time = Helper::string_to_time_t(fields.at(index++));
        auto end_time = Helper::string_to_time_t(fields.at(index++));
        std::string person = fields.at(index);

        target = std::make_unique<ReservationEntity>(ReservationEntity(*table_ptr, start_time, end_time, person));
        target.get()->id = id.value();

        return true;

    }

    int ReservationEntity::get_persitable_prop_count()
    {
        return this->persitable_prop_count;
    }

    bool ReservationEntity::match_convert_ptr(ReservationEntity *t, ReservationEntity *s, BaseEntity &target, BaseEntity &source)
    {
        t = dynamic_cast<ReservationEntity *>(&target);
        s = dynamic_cast<ReservationEntity *>(&source);

        auto id3 = Helper::id_to_string(t->id);
        auto id4 = Helper::id_to_string(s->id);

        return t != nullptr && s != nullptr;
    }

    auto ReservationEntity::match_by_id(BaseEntity &target, BaseEntity &source) noexcept -> cpp::result<bool, std::string>
    {
        ReservationEntity *t, *s;

        t = dynamic_cast<ReservationEntity *>(&target);
        s = dynamic_cast<ReservationEntity *>(&source);

        if (t == nullptr || s == nullptr)
        {
            return cpp::fail("Target or source not of type Entities::TableEntity.");
        }

        return t->id == s->id;
    }

    auto ReservationEntity::match_by_table_x_y(BaseEntity &target, BaseEntity &source) noexcept -> cpp::result<bool, std::string>
    {
        ReservationEntity *t, *s;

        t = dynamic_cast<ReservationEntity *>(&target);
        s = dynamic_cast<ReservationEntity *>(&source);

        if (t == nullptr || s == nullptr)
        {
            return cpp::fail("Target or source not of type Entities::TableEntity.");
        }

        return 
            t->table.get()->x == s->table.get()->x
            && t->table.get()->y == s->table.get()->y;
    }

    auto ReservationEntity::match_any(BaseEntity &target, BaseEntity &source) noexcept -> cpp::result<bool, std::string>
    {
        ReservationEntity *t, *s;

        t = dynamic_cast<ReservationEntity *>(&target);

        if (t == nullptr)
        {
            return cpp::fail("Target or source not of type Entities::TableEntity.");
        }

        return true;
    }

    auto ReservationEntity::match_open_reservation(BaseEntity &target, BaseEntity &source) noexcept -> cpp::result<bool, std::string>
    {
        ReservationEntity *t, *s;

        t = dynamic_cast<ReservationEntity *>(&target);

        if (t == nullptr)
        {
            return cpp::fail("Target or source not of type Entities::TableEntity.");
        }

        return t->end_time == 0;
    }

}
