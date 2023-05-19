#pragma once

#include <string>
#include "result.hpp"

namespace DataBase
{
    class DbConnector
    {
        private:
            std::string connection;
            auto create_file_if_not_exists(std::string &path) noexcept -> cpp::result<bool, std::string>;
            auto create_dictionary_if_not_exists(std::string &path) noexcept -> cpp::result<bool, std::string>;
            static std::unique_ptr<DbConnector> private_instance;
            DbConnector(const std::string connection);
            static bool has_instance();

        public:
            ~DbConnector();
            static void init_connector(const std::string &str);
            static DbConnector * instance();
            std::string get_connection_string();
            auto init_db_structure() noexcept -> cpp::result<bool, std::string>;
            auto get_table_layout_path() noexcept -> cpp::result<std::string, std::string>;
            auto get_reservation_path(const tm &time) noexcept -> cpp::result<std::string, std::string>;
            void drop_db();
    };
}



