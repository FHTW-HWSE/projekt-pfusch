#pragma once

#include "Base.hpp"
#include "BaseEntity.hpp"

namespace Entities
{
    class TableEntity : public BaseEntity
    {
        private:

        protected:
            virtual bool isEqual(const BaseEntity& obj) const override;

        public:
            static const int persitable_prop_count = 3 + BaseEntity::persitable_prop_count;
            //int id;
            int x;
            int y;
            unsigned int capacity;
            TableEntity();
            TableEntity(int x, int y, unsigned int capacity);
            TableEntity(const TableEntity &table);
            ~TableEntity();
            //overrides
            virtual std::unique_ptr<BaseEntity> clone() const override;
            virtual std::string parse_to_csv() override;
            virtual auto parse_from_csv(std::unique_ptr<BaseEntity> &target, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string> override;
            virtual int get_persitable_prop_count() override;
            virtual std::string to_string() override;
            //own functions
            static auto match_by_id(BaseEntity &target, BaseEntity &source) noexcept -> cpp::result<bool, std::string>;
            static auto match_by_x_and_y(BaseEntity &target, BaseEntity &sourcex) noexcept -> cpp::result<bool, std::string>;
            static auto match_any(BaseEntity &target, BaseEntity &source) noexcept -> cpp::result<bool, std::string>;
    };
}
