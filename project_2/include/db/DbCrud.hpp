#pragma once

#include "DbCrudBase.hpp"

namespace DataBase
{
    class DbCrud : public DataBase::DbCrudBase
    {
      public:
        DbCrud(){};
        ~DbCrud(){};
        auto create_record(Entities::BaseEntity &e, std::string filename) noexcept -> cpp::result<bool, std::string> override;
        auto read_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, Entities::BaseEntity &source, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string> override;
        auto read_all_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, Entities::BaseEntity &type, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string> override;
        auto update_record(Entities::BaseEntity &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string> override;
        auto delete_record(Entities::BaseEntity &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string> override;
    };
}
