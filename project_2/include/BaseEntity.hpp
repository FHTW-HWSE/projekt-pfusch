#pragma once

#include <string>
#include <vector>
#include <memory>
#include "uuid.hpp"
#include "result.hpp"

namespace Entities
{
    class BaseEntity
    {
        private:
            static const int persitable_prop_count = 1;

        protected:
            static int next_id;

        public:
            // typedef cpp::result<bool, std::string> (*MATCH_FUNC)(std::unique_ptr<BaseEntity> &b, std::vector<std::string> &fields, int &index) noexcept;
            typedef cpp::result<bool, std::string> (*MATCH_FUNC)(std::unique_ptr<BaseEntity> &target, std::unique_ptr<BaseEntity> &source) noexcept;
            uuids::uuid id;
            virtual ~BaseEntity();
            virtual std::string parse_to_csv();
            virtual auto parse_from_csv(std::unique_ptr<BaseEntity> &target, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string> = 0;
            virtual int get_persitable_prop_count();
            uuids::uuid create_new_uuid();
            static const char delimiter = ';';
    };
}


