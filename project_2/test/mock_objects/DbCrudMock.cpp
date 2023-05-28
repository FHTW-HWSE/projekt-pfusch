#include "DbCrudMock.hpp"

namespace DataBase
{
    auto DbCrudMock::create_record(std::unique_ptr<Entities::BaseEntity> &e, std::string filename) noexcept -> cpp::result<bool, std::string>
    {
      return true;
    }

    auto DbCrudMock::read_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, std::unique_ptr<Entities::BaseEntity> &source, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
    {
      return true;
    }

    auto DbCrudMock::read_all_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, std::unique_ptr<Entities::BaseEntity> &type, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
    {
      return true;
    }

    auto DbCrudMock::update_record(std::unique_ptr<Entities::BaseEntity> &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
    {
      return true; 
    }

    auto DbCrudMock::delete_record(std::unique_ptr<Entities::BaseEntity> &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
    {
      return true;
    }
}
