#pragma once

#include <string>
#include "result.hpp"
#include "DbConnectorBase.hpp"

namespace DataBase
{
    class DbConnector : public DataBase::DbConnectorBase
    {
        private:
            //fields
            std::string connection;
            std::unique_ptr<DataBase::DbCrudBase> crud;

            //virtual functions
            auto create_file_if_not_exists(std::string &path) noexcept -> cpp::result<bool, std::string>;
            auto create_dictionary_if_not_exists(std::string &path) noexcept -> cpp::result<bool, std::string>;

        public:
            //cnst
            DbConnector(const std::string connection, std::unique_ptr<DataBase::DbCrudBase> &crud);
            //dstr
            ~DbConnector(){};
            //override functions
            std::string get_connection_string() override;
            auto init_db() noexcept -> cpp::result<bool, std::string> override;
            auto get_table_layout_path() noexcept -> cpp::result<std::string, std::string> override;
            auto get_reservation_path() noexcept -> cpp::result<std::string, std::string> override;
            DataBase::DbCrudBase * get_crud() override;
    };
}



