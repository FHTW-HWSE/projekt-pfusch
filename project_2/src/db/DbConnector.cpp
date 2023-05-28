#include <fstream>
#include <time.h>
#include <string>
#include <filesystem>
#include <cstdlib> 

#include "DbConnector.hpp"
#include "DbConnectorBase.hpp"
#include "result.hpp"
#include "conversion_helper.hpp"

namespace DataBase
{
    static const std::string TABLE_DICT_PATH = "table_layout/";
    static const std::string TABLE_LAYOUT_PATH = TABLE_DICT_PATH + "table_layout.csv";
    static const std::string RESERVATIONS_DICT_PATH = "reservations/";
    static const std::string TRESERVATIONS_PATH = RESERVATIONS_DICT_PATH + "reservations.csv";

    DbConnector::DbConnector(const std::string connection, std::unique_ptr<DataBase::DbCrudBase> &crud)
    {
        this->connection = connection;
        this->crud = std::unique_ptr<DataBase::DbCrudBase>(nullptr);
        this->crud.swap(crud);
    }
        
    //tested
    std::string DbConnector::get_connection_string()
    {
        return this->connection;
    }

    //no unit test
    auto DbConnector::create_file_if_not_exists(std::string &path) noexcept -> cpp::result<bool, std::string>
    {
        std::fstream fs;

        try
        {
            fs.open(path, std::ios::out | std::ios::app);
        }
        catch (const std::ifstream::failure &e)
        {
            fs.close();
            return cpp::fail(e.what());
        }

        fs.close();
        return true;
    }

    //TODO: mocking
    auto DbConnector::create_dictionary_if_not_exists(std::string &path) noexcept -> cpp::result<bool, std::string>
    {
        try
        {
            return std::filesystem::create_directory(path);
        }
        catch(std::filesystem::filesystem_error &e)
        {
            return cpp::fail(e.what());
        }

        return false;
    }


    //no unit test
    auto DbConnector::get_table_layout_path() noexcept -> cpp::result<std::string, std::string>
    {
        std::string path = this->get_connection_string() + TABLE_LAYOUT_PATH;

        auto r_create = create_file_if_not_exists(path);

        return path;
    }

    //no unit test
    auto DbConnector::get_reservation_path() noexcept -> cpp::result<std::string, std::string>
    {
        // char buffer[15];
        // size_t format = strftime(buffer, 15, "YYYY-MM-DD", &time);
        std::string path = this->get_connection_string() + TRESERVATIONS_PATH;

        auto r_create = create_file_if_not_exists(path);

        // auto blub = Helper::tm_to_Ymd(time);

        // path.append(blub);
        // path.append(".csv");
        return path;
    }


    //no unit test
    auto DbConnector::init_db() noexcept -> cpp::result<bool, std::string>
    {
        std::string tables_path = this->connection + TABLE_DICT_PATH;
        auto r_tables = this->create_dictionary_if_not_exists(tables_path);

        if(r_tables.has_error()){
            return cpp::fail(r_tables.error());
        }

        std::string reservation_path = this->connection + RESERVATIONS_DICT_PATH;

        auto r_res = this->create_dictionary_if_not_exists(reservation_path);

        if(r_res.has_error()){
            return cpp::fail(r_res.error());
        }

        return true;
    }

    DataBase::DbCrudBase * DbConnector::get_crud()
    {
        return this->crud.get();
    }

}
