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
        auto parse_from_csv(std::unique_ptr<BaseEntity> &target, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string> override;
        int get_persitable_prop_count() override;
        static auto match_by_id(std::unique_ptr<BaseEntity> &target, std::unique_ptr<BaseEntity> &source) noexcept -> cpp::result<bool, std::string>;
        static auto match_by_x_and_y(std::unique_ptr<BaseEntity> &target, std::unique_ptr<BaseEntity> &sourcex) noexcept -> cpp::result<bool, std::string>;
        static auto match_any(std::unique_ptr<BaseEntity> &target, std::unique_ptr<BaseEntity> &source) noexcept -> cpp::result<bool, std::string>;
    };
}
