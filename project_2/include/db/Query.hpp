#include <stdlib.h>
#include "result.hpp"
#include "TableEntity.hpp"

namespace DataBase
{
    class Query
    {
        public:
            Query();
            ~Query();
            // TableEntity
            static auto create_table(Entities::BaseEntity &t) noexcept -> cpp::result<bool, std::string>;
            static auto read_tables_by_x_y(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables, Entities::BaseEntity &table) noexcept -> cpp::result<bool, std::string>;
            static auto read_tables_by_id(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables, Entities::BaseEntity &table) noexcept -> cpp::result<bool, std::string>;
            static auto read_all_tables(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables) noexcept -> cpp::result<bool, std::string>;
            static auto update_table(Entities::BaseEntity &table) noexcept -> cpp::result<bool, std::string>;
            static auto delete_table(Entities::BaseEntity &table) noexcept -> cpp::result<bool, std::string>;
            // ReservationEntity
            static auto create_reservation(Entities::BaseEntity &t) noexcept -> cpp::result<bool, std::string>;
            static auto read_all_reservations(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables) noexcept -> cpp::result<bool, std::string>;
            static auto read_reservations_by_id(std::vector<std::unique_ptr<Entities::BaseEntity>> &reservations, Entities::BaseEntity &reservation) noexcept -> cpp::result<bool, std::string>;
            static auto read_reservations_by_x_y(std::vector<std::unique_ptr<Entities::BaseEntity>> &reservations, Entities::BaseEntity &reservation) noexcept -> cpp::result<bool, std::string>;
            static auto read_all_open_reservations(std::vector<std::unique_ptr<Entities::BaseEntity>> &reservations, Entities::BaseEntity &reservation) noexcept -> cpp::result<bool, std::string>;
            static auto update_reservation(Entities::BaseEntity &reservation) noexcept -> cpp::result<bool, std::string>;
            static auto delete_reservation(Entities::BaseEntity &reservation) noexcept -> cpp::result<bool, std::string>;
    };
}

