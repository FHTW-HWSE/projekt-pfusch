#include "ReservationEntity.hpp"

namespace Entities
{
    ReservationEntity::ReservationEntity
    (   
        TableEntity *table_entity, 
        std::string contact_person
    )
    {
        this->table_entity = table_entity;
        this->contact_person = contact_person;
        this->persitable_prop_count = 2 + table_entity->get_persitable_prop_count();
    }

    ReservationEntity::~ReservationEntity()
    {
    }

    std::string ReservationEntity::parse_to_csv(){
        return BaseEntity::parse_to_csv()
            + this->table_entity->parse_to_csv() 
            + this->delimiter + this->contact_person;
    }
}
