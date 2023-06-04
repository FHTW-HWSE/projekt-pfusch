#pragma once

#include <queue>

#include "DbCrudBase.hpp"

namespace DataBase
{
    class DbCrudMock : public DataBase::DbCrudBase
    {
      private:
        struct queue_item
        {
          const cpp::result<bool, std::string> result;
          std::queue<std::unique_ptr<Entities::BaseEntity>> items;
        };

        std::queue<std::unique_ptr<struct queue_item>> create_record_queue;
        std::queue<std::unique_ptr<struct queue_item>> read_records_queue;
        std::queue<std::unique_ptr<struct queue_item>> read_all_records_queue;
        std::queue<std::unique_ptr<struct queue_item>> update_record_queue;
        std::queue<std::unique_ptr<struct queue_item>> delete_record_queue;

        void push_into_queue(std::queue<std::unique_ptr<struct queue_item>> &queue, const std::vector<std::unique_ptr<Entities::BaseEntity>> &items, const cpp::result<bool, std::string> &result);
        auto pop_from_queue(std::queue<std::unique_ptr<struct queue_item>> &queue, std::vector<std::unique_ptr<Entities::BaseEntity>> &items) noexcept -> cpp::result<bool, std::string>;

      public:
        DbCrudMock(){};
        ~DbCrudMock(){};

        void mock_create_record(const cpp::result<bool, std::string> &result);
        void mock_read_records(const cpp::result<bool, std::string> &result, const std::vector<std::unique_ptr<Entities::BaseEntity>> &items);
        void mock_read_all_records(const cpp::result<bool, std::string> &result, const std::vector<std::unique_ptr<Entities::BaseEntity>> &items);
        void mock_update_record(const cpp::result<bool, std::string> &result);
        void mock_delete_record(const cpp::result<bool, std::string> &result);

        auto create_record(Entities::BaseEntity &e, std::string filename) noexcept -> cpp::result<bool, std::string> override;
        auto read_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, Entities::BaseEntity &source, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string> override;
        auto read_all_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, Entities::BaseEntity &type, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string> override;
        auto update_record(Entities::BaseEntity &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string> override;
        auto delete_record(Entities::BaseEntity &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string> override;
    };
}
