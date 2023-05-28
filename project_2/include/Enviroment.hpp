#pragma once

#include <string>
#include "result.hpp"
#include "DbConnectorBase.hpp"

namespace Enviroment
{
    class Config
    {
        private:
            //cnst
            Config(){};
            //fields
            std::unique_ptr<DataBase::DbConnectorBase> db_connector;

        public:
            //dstr
            ~Config(){};
            //static functions
            static void init(std::unique_ptr<DataBase::DbConnectorBase> &db_connector);
            static Config * instance();
            //instance functions
            DataBase::DbConnectorBase * get_db_con();
    };
}



