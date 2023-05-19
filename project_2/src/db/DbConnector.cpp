#include <fstream>
#include <time.h>
#include <string>
#include <filesystem>
#include <cstdlib> 

#include "DbConnector.hpp"
#include "result.hpp"
#include "conversion_helper.hpp"

namespace DataBase
{
    static const std::string TABLE_DICT_PATH = "table_layout/";
    static const std::string TABLE_LAYOUT_PATH = TABLE_DICT_PATH + "table_layout.csv";
    static const std::string RESERVATIONS_DICT_PATH = "reservations/";

    std::unique_ptr<DbConnector> DbConnector::private_instance;


    DbConnector::DbConnector(const std::string connection){
        this->connection = connection;
    }

    DbConnector::~DbConnector(){
        
    }

    //tested
    bool DbConnector::has_instance(){
        return
            DbConnector::private_instance != nullptr
            || DbConnector::private_instance.get() != nullptr;
    }

    //tested
    void DbConnector::init_connector(const std::string &str)
    {
        if (!has_instance())
        {
            DbConnector::private_instance = 
                std::make_unique<DbConnector>(DbConnector(str));
        }
        else
        {
            DbConnector::instance()->connection = str;
        }
    }
        
    //tested
    DbConnector * DbConnector::instance()
    {
        if(!has_instance()){
            DbConnector::private_instance = 
                std::make_unique<DbConnector>(DbConnector("./"));
        }

        return DbConnector::private_instance.get();
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


    //TODO: mocking
    auto DbConnector::get_table_layout_path() noexcept -> cpp::result<std::string, std::string>
    {
        std::string path = this->get_connection_string() + TABLE_LAYOUT_PATH;

        auto r_create = create_file_if_not_exists(path);

        return path;
    }

    //tested
    auto DbConnector::get_reservation_path(const tm &time) noexcept -> cpp::result<std::string, std::string>
    {
        char buffer[15];
        size_t format = strftime(buffer, 15, "YYYY-MM-DD", &time);
        std::string output = this->get_connection_string();

        auto blub = Helper::tm_to_Ymd(time);

        output.append(blub);
        output.append(".csv");
        return output;
    }


    //TODO: mocking
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

    void DbConnector::drop_db()
    {
        std::string path = DbConnector::instance()->get_connection_string();

        std::string table_dict = path + TABLE_DICT_PATH + "*";
        std::string reservation_dict = path + RESERVATIONS_DICT_PATH + "*";
        //rm /path/to/directory/*

        std::string rm = "rm ";
        std::string rm_table = rm + table_dict;
        std::string rm_res = rm + reservation_dict;

        system(rm_table.c_str());
        system(rm_res.c_str());
    }

}
