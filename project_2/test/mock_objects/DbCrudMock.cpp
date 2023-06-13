#include "DbCrudMock.hpp"

namespace DataBase
{
  void DbCrudMock::push_into_queue(std::queue<std::unique_ptr<struct queue_item>> &queue, const std::vector<std::unique_ptr<Entities::BaseEntity>> &items, const cpp::result<bool, std::string> &result)
  {
    struct queue_item item = { .result = result };

    for (const auto &s : items)
		{
      auto b = s.get()->clone();
			item.items.push(std::move(b));
		}

    auto node_ptr = std::make_unique<struct queue_item>(std::move(item));

    queue.push(std::move(node_ptr));
  }

  auto DbCrudMock::pop_from_queue(std::queue<std::unique_ptr<struct queue_item>> &queue, std::vector<std::unique_ptr<Entities::BaseEntity>> &items) noexcept -> cpp::result<bool, std::string>
  {
    if(queue.empty())
    {
      return cpp::fail("no mocked result provided.");
    }

    auto elem = std::move(queue.front());
    queue.pop();

    auto queue_items = std::move(elem.get()->items);

    while (queue_items.empty() == false)
    {
      auto item = std::move(queue_items.front());
      queue_items.pop();
      items.push_back(std::move(item));
    }

    return elem.get()->result;
  }

  void DbCrudMock::mock_create_record(const cpp::result<bool, std::string> &result)
  {
    std::vector<std::unique_ptr<Entities::BaseEntity>> items;
    push_into_queue(this->create_record_queue, items, result);
  }

  auto DbCrudMock::create_record(Entities::BaseEntity &e, std::string filename) noexcept -> cpp::result<bool, std::string>
  {
    std::vector<std::unique_ptr<Entities::BaseEntity>> items;
    return pop_from_queue(this->create_record_queue, items);
  }

  void DbCrudMock::mock_read_records(const cpp::result<bool, std::string> &result, const std::vector<std::unique_ptr<Entities::BaseEntity>> &items)
  {
    push_into_queue(this->read_records_queue, items, result);
  }

  auto DbCrudMock::read_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, Entities::BaseEntity &source, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
  {
    return pop_from_queue(this->read_records_queue, e);
  }

  void DbCrudMock::mock_read_all_records(const cpp::result<bool, std::string> &result, const std::vector<std::unique_ptr<Entities::BaseEntity>> &items)
  {
    push_into_queue(this->read_all_records_queue, items, result);
  }

  auto DbCrudMock::read_all_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, Entities::BaseEntity &type, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
  {
    return pop_from_queue(this->read_all_records_queue, e);
  }

  void DbCrudMock::mock_update_record(const cpp::result<bool, std::string> &result)
  {
    std::vector<std::unique_ptr<Entities::BaseEntity>> items;
    push_into_queue(this->update_record_queue, items, result);
  }

  auto DbCrudMock::update_record(Entities::BaseEntity &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
  {
    std::vector<std::unique_ptr<Entities::BaseEntity>> items;
    return pop_from_queue(this->update_record_queue, items);
  }

  void DbCrudMock::mock_delete_record(const cpp::result<bool, std::string> &result)
  {
    std::vector<std::unique_ptr<Entities::BaseEntity>> items;
    push_into_queue(this->delete_record_queue, items, result);
  }

  auto DbCrudMock::delete_record(Entities::BaseEntity &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
  {
    std::vector<std::unique_ptr<Entities::BaseEntity>> items;
    return pop_from_queue(this->delete_record_queue, items);
  }
}
