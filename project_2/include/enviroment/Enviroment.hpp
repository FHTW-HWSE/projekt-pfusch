#pragma once

#include <string>
#include "result.hpp"
#include "DbConnectorBase.hpp"
#include "InteractionBase.hpp"

namespace Enviroment
{
    class Config
    {
        private:
            //cnst
            Config(){};
            //fields
            std::unique_ptr<DataBase::DbConnectorBase> db_connector;
            std::unique_ptr<Interaction::InteractionBase> interaction;

        public:
            //dstr
            ~Config(){};
            //static functions
            static void init(std::unique_ptr<DataBase::DbConnectorBase> &db_connector, std::unique_ptr<Interaction::InteractionBase> &interaction);
            static Config * instance();
            //instance functions
            DataBase::DbConnectorBase * get_db_con();
            Interaction::InteractionBase * get_interaction();
    };
}



