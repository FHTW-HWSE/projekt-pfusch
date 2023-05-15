#pragma once

#include <string>

namespace DateBase
{
    class DbConnector
    {
    private:
        std::string connection;
        auto create_file_if_not_exists(std::string &path) noexcept -> cpp::result<bool, std::string>;
        auto create_dictionary_if_not_exists(std::string &path) noexcept -> cpp::result<bool, std::string>;

    public:
        DbConnector(std::string connection);
        ~DbConnector();
        std::string get_connection_string();
        auto init_db_structure() noexcept -> cpp::result<bool, std::string>;
        auto get_table_layout_path() noexcept -> cpp::result<std::string, std::string>;
        auto get_reservation_path(const tm &time) noexcept -> cpp::result<std::string, std::string>;
    };
}



