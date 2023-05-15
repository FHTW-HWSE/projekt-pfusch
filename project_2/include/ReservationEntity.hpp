#pragma once

#include <string>
#include <ctime>

#include "TableEntity.hpp"
#include "BaseEntity.hpp"

namespace Entities
{
    class ReservationEntity : BaseEntity
    {
    private:
        
    public:
        class TableEntity *table_entity;
        std::string contact_person;
        time_t start_time;
        time_t end_time;
        unsigned int persitable_prop_count;
        ReservationEntity(TableEntity *table_entity, std::string contact_person);
        ~ReservationEntity();
        virtual std::string parse_to_csv();
    };
}


