#pragma once

#include <string>
#include <ctime>

#include "Base.hpp"
#include "TableEntity.hpp"
#include "BaseEntity.hpp"

namespace Entities
{
    class ReservationEntity : public BaseEntity
    {
        private:

        protected:
            virtual bool isEqual(const BaseEntity& obj) const override;

        public:
            ReservationEntity(std::unique_ptr<Entities::TableEntity> &table, std::string &contact_person);
            ReservationEntity(const ReservationEntity &reservation);
            ~ReservationEntity();
            //fields
            static const int persitable_prop_count = 3 + TableEntity::persitable_prop_count;
            std::unique_ptr<Entities::TableEntity> table;
            std::string contact_person;
            time_t start_time;
            time_t end_time;
            //overrides
            virtual std::unique_ptr<BaseEntity> clone() const override;
            virtual std::string parse_to_csv() override;
            virtual auto parse_from_csv(std::unique_ptr<BaseEntity> &target, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string> override;
            virtual int get_persitable_prop_count() override;
    };
}


