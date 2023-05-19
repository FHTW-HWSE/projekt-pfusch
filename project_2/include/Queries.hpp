#include <stdlib.h>
#include "result.hpp"
#include "TableEntity.hpp"

namespace DataBase
{
    class Queries{
        public:
            Queries();
            ~Queries();
            auto static read_tables_by_x_y(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables, std::unique_ptr<Entities::BaseEntity> &table) noexcept -> cpp::result<bool, std::string>;
            auto static read_all_tables(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables) noexcept -> cpp::result<bool, std::string>;
            auto static create_table(std::unique_ptr<Entities::BaseEntity> &t) noexcept -> cpp::result<bool, std::string>;
            auto static read_tables_by_id(std::vector<std::unique_ptr<Entities::BaseEntity>> &tables, std::unique_ptr<Entities::BaseEntity> &table) noexcept -> cpp::result<bool, std::string>;
            auto static update_table(std::unique_ptr<Entities::BaseEntity> &table) noexcept -> cpp::result<bool, std::string>;
            auto static delete_table(std::unique_ptr<Entities::BaseEntity> &table) noexcept -> cpp::result<bool, std::string>;
    };
}

