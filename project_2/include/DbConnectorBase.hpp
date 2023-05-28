#pragma once

#include <string>
#include "result.hpp"
#include "DbCrudBase.hpp"

namespace DataBase
{
    class DbConnectorBase
    {
        private:
            //fields
            // std::string connection;
            // std::unique_ptr<DataBase::DbCrudBase> crud;
            //virtual functions
            // virtual auto create_file_if_not_exists(std::string &path) noexcept -> cpp::result<bool, std::string> = 0;
            // virtual auto create_dictionary_if_not_exists(std::string &path) noexcept -> cpp::result<bool, std::string> = 0;

        public:
            //dstr
            virtual ~DbConnectorBase(){};
            //virtual functions
            virtual std::string get_connection_string() = 0;
            virtual auto init_db() noexcept -> cpp::result<bool, std::string> = 0;
            virtual auto get_table_layout_path() noexcept -> cpp::result<std::string, std::string> = 0;
            virtual auto get_reservation_path() noexcept -> cpp::result<std::string, std::string> = 0;
            virtual DataBase::DbCrudBase * get_crud() = 0;
    };
}



