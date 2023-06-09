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
            //properties
            static const int persitable_prop_count = 1;
            static const char delimiter = ';';
            typedef cpp::result<bool, std::string> (*MATCH_FUNC)(BaseEntity &target, BaseEntity &source) noexcept;
            uuids::uuid id;
            //constructor
            BaseEntity();
            BaseEntity(const BaseEntity &b);
            //destructor
            virtual ~BaseEntity();
            //virtual pure functions
            virtual std::unique_ptr<BaseEntity> clone() const = 0;
            virtual auto parse_from_csv(std::unique_ptr<BaseEntity> &target, std::vector<std::string> &fields, int &index) noexcept -> cpp::result<bool, std::string> = 0;
            //virtual functins
            virtual std::string parse_to_csv();
            virtual int get_persitable_prop_count();
            //functions
            uuids::uuid create_new_uuid();
    };

    bool operator==(const BaseEntity&, const BaseEntity&);
}


