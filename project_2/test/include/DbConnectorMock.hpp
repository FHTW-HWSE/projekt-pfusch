#pragma once

#include "DbConnectorBase.hpp"

namespace DataBase
{
    class DbConnectorMock : public DataBase::DbConnectorBase
    {
        private:
            //fields
            std::string connection;
            std::unique_ptr<DataBase::DbCrudBase> crud;
            //virtual functions
        public:
            //dstr
            DbConnectorMock(std::string &connection, std::unique_ptr<DataBase::DbCrudBase> &crud);
            ~DbConnectorMock(){};
            //virtual functions
            std::string get_connection_string() override;
            auto init_db() noexcept -> cpp::result<bool, std::string> override;
            auto get_table_layout_path() noexcept -> cpp::result<std::string, std::string> override;
            auto get_reservation_path() noexcept -> cpp::result<std::string, std::string> override;
            DataBase::DbCrudBase * get_crud() override;
    };
}



