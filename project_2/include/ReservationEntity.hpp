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
            static bool match_convert_ptr(ReservationEntity *t, ReservationEntity *s, BaseEntity &target, BaseEntity &source);

        protected:
            virtual bool isEqual(const BaseEntity& obj) const override;

        public:
            //constructor
            ReservationEntity();
            ReservationEntity(Entities::TableEntity &table, std::string &contact_person);
            ReservationEntity(Entities::TableEntity &table, time_t &start_time, time_t &end_time, std::string &contact_person);
            ReservationEntity(const ReservationEntity &reservation);
            //destructor
            ~ReservationEntity();
            //properties
            static const int persitable_prop_count = 3 + BaseEntity::persitable_prop_count + TableEntity::persitable_prop_count;
            std::unique_ptr<Entities::TableEntity> table;
            std::string contact_person;
            time_t start_time;
            time_t end_time;
            //overrides
            virtual std::unique_ptr<BaseEntity> clone() const override;
            virtual std::string parse_to_csv() override;
            virtual auto parse_from_csv(std::unique_ptr<BaseEntity> &target, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string> override;
            virtual int get_persitable_prop_count() override;
            //functions
            static auto match_by_id(BaseEntity &target, BaseEntity &source) noexcept -> cpp::result<bool, std::string>;
            static auto match_by_table_x_y(BaseEntity &target, BaseEntity &source) noexcept -> cpp::result<bool, std::string>;
            static auto match_any(BaseEntity &target, BaseEntity &source) noexcept -> cpp::result<bool, std::string>;
            static auto match_open_reservation(BaseEntity &target, BaseEntity &source) noexcept -> cpp::result<bool, std::string>;

    };
}


