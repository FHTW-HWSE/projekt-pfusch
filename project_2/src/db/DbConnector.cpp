#include <fstream>
#include <time.h>
#include <string>
#include <filesystem>

#include "DbConnector.hpp"
#include "result.hpp"

namespace DataBase
{
    static const std::string TABLE_DICT_PATH = "table_layout/";
    static const std::string TABLE_LAYOUT_PATH = TABLE_DICT_PATH + "table_layout.csv";
    static const std::string RESERVATIONS_DICT_PATH = "reservations/";

    std::unique_ptr<DbConnector> DbConnector::private_instance;


    DbConnector::DbConnector(std::string connection){
        this->connection = connection;
    }

    DbConnector::~DbConnector(){
        
    }

    bool DbConnector::has_instance(){
        return
            DbConnector::private_instance != nullptr
            || DbConnector::private_instance.get() != nullptr;
    }

    void DbConnector::init_connector(std::string &str)
    {
        if (!has_instance())
        {
            DbConnector::private_instance = std::make_unique<DbConnector>(DbConnector(str));
        }
        else
        {
            DbConnector::instance()->connection = str;
        }
    }
        
    DbConnector * DbConnector::instance()
    {
        return DbConnector::private_instance.get();
    }

    std::string DbConnector::get_connection_string()
    {
        return this->connection;
    }

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

    auto DbConnector::get_table_layout_path() noexcept -> cpp::result<std::string, std::string>
    {
        std::string path = this->get_connection_string() + TABLE_LAYOUT_PATH;

        auto r_create = create_file_if_not_exists(path);

        return path;
    }

    auto DbConnector::get_reservation_path(const tm &time) noexcept -> cpp::result<std::string, std::string>
    {
        char buffer[15];
        size_t format = strftime(buffer, 15, "YYYY-MM-DD", &time);
        std::string output = this->get_connection_string();
        output.append(buffer);
        output.append(".csv");
        return output;
    }


    auto DbConnector::init_db_structure() noexcept -> cpp::result<bool, std::string>
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

}
