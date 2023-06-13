#pragma once

#include "BaseEntity.hpp"
#include "result.hpp"

namespace DataBase
{
    class DbCrudBase
    {
      public:
        virtual ~DbCrudBase(){};
        virtual auto create_record(Entities::BaseEntity &e, std::string filename) noexcept -> cpp::result<bool, std::string> = 0;
        virtual auto read_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, Entities::BaseEntity &source, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string> = 0;
        virtual auto read_all_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, Entities::BaseEntity &type, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string> = 0;
        virtual auto update_record(Entities::BaseEntity &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string> = 0;
        virtual auto delete_record(Entities::BaseEntity &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string> = 0;
    };
}