#include "Enviroment.hpp"

namespace Enviroment
{
    Config * Config::instance()
    {
        static Config INSTANCE;

        if(INSTANCE.db_connector == nullptr)
        {
            INSTANCE.db_connector = std::unique_ptr<DataBase::DbConnectorBase>(nullptr);
        }

        return &INSTANCE;
    }

    void Config::init(std::unique_ptr<DataBase::DbConnectorBase> &db_connector, std::unique_ptr<Interaction::InteractionBase> &interaction)
    {
        Config::instance()->db_connector.swap(db_connector);
        Config::instance()->interaction.swap(interaction);
    }


    DataBase::DbConnectorBase * Config::get_db_con()
    {
        return Config::instance()->db_connector.get();
    }

    Interaction::InteractionBase * Config::get_interaction()
    {
        return Config::instance()->interaction.get();
    }

}


