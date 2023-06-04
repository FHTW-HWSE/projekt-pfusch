#pragma once

#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <vector>
#include <cassert>
#include "uuid.hpp"
#include "result.hpp"

namespace Entities
{
    class BaseEntity
    {
        private:

        protected:
            friend bool operator==(const BaseEntity&, const BaseEntity&);
            virtual bool isEqual(const BaseEntity& obj) const;

        public:
            static const int persitable_prop_count = 1;
            typedef cpp::result<bool, std::string> (*MATCH_FUNC)(BaseEntity &target, BaseEntity &source) noexcept;
            uuids::uuid id;
            BaseEntity();
            BaseEntity(const BaseEntity &b);
            virtual ~BaseEntity();
            virtual std::unique_ptr<BaseEntity> clone() const = 0;
            virtual auto parse_from_csv(std::unique_ptr<BaseEntity> &target, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string> = 0;
            virtual std::string parse_to_csv();
            virtual int get_persitable_prop_count();
            uuids::uuid create_new_uuid();
            static const char delimiter = ';';
    };

    bool operator==(const BaseEntity&, const BaseEntity&);
}


