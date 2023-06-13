#include <fstream>
#include <time.h>
#include <string>
#include <filesystem>
#include <cstdlib> 

#include "result.hpp"
#include "conversion_helper.hpp"

#include "DbConnectorMock.hpp"

namespace DataBase
{
    static const std::string TABLE_DICT_PATH = "table_layout/";
    static const std::string TABLE_LAYOUT_PATH = TABLE_DICT_PATH + "table_layout.csv";
    static const std::string RESERVATIONS_DICT_PATH = "reservations/";
    static const std::string RESERVATIONS_LAYOUT_PATH = RESERVATIONS_DICT_PATH + "reservations.csv";

    DbConnectorMock::DbConnectorMock(std::string &connection, std::unique_ptr<DataBase::DbCrudBase> &crud)
    {
        this->connection = connection;
        this->crud = std::unique_ptr<DataBase::DbCrudBase>(nullptr);
        this->crud.swap(crud);
    }

    std::string DbConnectorMock::get_connection_string()
    {
        return this->connection;
    }

    auto DbConnectorMock::init_db() noexcept -> cpp::result<bool, std::string>
    {
        return true;
    }

    auto DbConnectorMock::get_table_layout_path() noexcept -> cpp::result<std::string, std::string>
    {
        return this->connection + TABLE_LAYOUT_PATH;
    }

    auto DbConnectorMock::get_reservation_path() noexcept -> cpp::result<std::string, std::string>
    {
        return this->connection + RESERVATIONS_LAYOUT_PATH;
    }

    DataBase::DbCrudBase * DbConnectorMock::get_crud()
    {
        return this->crud.get();
    }
}
