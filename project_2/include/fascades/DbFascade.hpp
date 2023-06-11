#pragma once

#include "Base.hpp"
#include "TableEntity.hpp"
#include "ReservationEntity.hpp"

namespace Fascades
{
    class DbFascade
    {
        private:

            template<class T>
            static auto fill_vector(std::vector<std::unique_ptr<T>> &tables, std::vector<std::unique_ptr<Entities::BaseEntity>> &items) noexcept -> cpp::result<bool, std::string>;
            // static auto fill_tables_vector(std::vector<std::unique_ptr<Entities::TableEntity>> &tables, std::vector<std::unique_ptr<Entities::BaseEntity>> &items) noexcept -> cpp::result<bool, std::string>;

        public:
            // TableEntity
            static auto create_table(Entities::TableEntity &table) noexcept -> cpp::result<bool, std::string>;
            static auto get_tables_by_x_y(std::vector<std::unique_ptr<Entities::TableEntity>> &tables, const int &x, const int &y) noexcept -> cpp::result<bool, std::string>;
            static auto get_tables_by_id(std::vector<std::unique_ptr<Entities::TableEntity>> &tables, const uuids::uuid &id) noexcept -> cpp::result<bool, std::string>;
            static auto get_all_tables(std::vector<std::unique_ptr<Entities::TableEntity>> &tables) noexcept -> cpp::result<bool, std::string>;
            static auto update_table(Entities::TableEntity &table) noexcept -> cpp::result<bool, std::string>;
            static auto delete_table(Entities::TableEntity &table) noexcept -> cpp::result<bool, std::string>;
            // ReservationEntity
            static auto create_reservation(Entities::ReservationEntity &table) noexcept -> cpp::result<bool, std::string>;
            static auto get_reservations_by_x_y(std::vector<std::unique_ptr<Entities::ReservationEntity>> &reservations, const int &x, const int &y) noexcept -> cpp::result<bool, std::string>;
            static auto get_reservations_by_id(std::vector<std::unique_ptr<Entities::ReservationEntity>> &reservations, const uuids::uuid &id) noexcept -> cpp::result<bool, std::string>;
            static auto get_all_reservations(std::vector<std::unique_ptr<Entities::ReservationEntity>> &reservations) noexcept -> cpp::result<bool, std::string>;
            static auto get_all_open_reservations(std::vector<std::unique_ptr<Entities::ReservationEntity>> &reservations) noexcept -> cpp::result<bool, std::string>;
            static auto update_reservation(Entities::ReservationEntity &reservation) noexcept -> cpp::result<bool, std::string>;
            static auto delete_reservation(Entities::ReservationEntity &reservation) noexcept -> cpp::result<bool, std::string>;
    };
}
