#pragma once

#include "Base.hpp"
#include "BaseEntity.hpp"

namespace Entities
{
    class TableEntity : public BaseEntity
    {
    private:
        static const int persitable_prop_count = 3;
    public:
        //int id;
        int x;
        int y;
        unsigned int capacity;
        TableEntity(int x, int y, unsigned int capacity);
        ~TableEntity();
        std::string parse_to_csv() override;
        auto db_read_record(std::unique_ptr<BaseEntity> &b, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string> override;
        auto db_write_record() noexcept -> cpp::result<std::string, std::string> override;
        bool equals(const BaseEntity &b) override;
        bool equals(const std::unique_ptr<BaseEntity> &b) override;
        int get_persitable_prop_count() override;
        static auto db_match_record_by_id(std::unique_ptr<BaseEntity> &source, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string>;
        static auto db_match_record_by_x_and_y(std::unique_ptr<BaseEntity> &source, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string>;
        static auto db_match_any(std::unique_ptr<BaseEntity> &source, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string>;
    };
}
