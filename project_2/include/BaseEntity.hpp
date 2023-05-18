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
            typedef cpp::result<bool, std::string> (*MATCH_FUNC)(std::unique_ptr<BaseEntity> &b, std::vector<std::string> &fields, int &index) noexcept;
            uuids::uuid id;
            virtual ~BaseEntity();
            virtual std::string parse_to_csv();
            virtual auto db_read_record(std::unique_ptr<BaseEntity> &b, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string> = 0;
            virtual auto db_write_record() noexcept -> cpp::result<std::string, std::string> = 0;
            virtual int get_persitable_prop_count();
            uuids::uuid create_new_uuid();
            static const char delimiter = ';';
            // virtual bool equals(const BaseEntity &b) = 0;
            // virtual bool equals(const std::unique_ptr<BaseEntity> &b) = 0;
    };
}


