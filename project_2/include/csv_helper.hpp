#pragma once

#include "Base.hpp"

// Result create_record(unique_ptr<Entities::BaseEntity> &e, string filename);
// Result read_record(unique_ptr<Entities::BaseEntity> &e, string filename);
// Result read_all_records(vector<unique_ptr<Entities::BaseEntity>> &e, Entities::BaseEntity &type, string filename);
// Result update_record(unique_ptr<Entities::BaseEntity> &e, string filename);
// Result delete_record(unique_ptr<Entities::BaseEntity> &e, string filename);

namespace csv_helper
{
    auto create_record(std::unique_ptr<Entities::BaseEntity> &e, std::string filename) noexcept -> cpp::result<bool, std::string>;
    auto read_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, std::unique_ptr<Entities::BaseEntity> &source, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>;
    auto read_all_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, std::unique_ptr<Entities::BaseEntity> &type, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>;
    auto update_record(std::unique_ptr<Entities::BaseEntity> &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>;
    auto delete_record(std::unique_ptr<Entities::BaseEntity> &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>;
}