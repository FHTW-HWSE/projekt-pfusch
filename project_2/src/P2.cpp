#include "Base.hpp"
#include "Enviroment.hpp"
#include "DbConnector.hpp"
#include "DbCrud.hpp"
#include "DbFascade.hpp"
#include "UiFascade.hpp"
#include <iostream>
#include "UIMainMenu.hpp"
#include "Interaction.hpp"

int main(int argc, char* args[])
{
#pragma region init enviroment

    auto crud = std::unique_ptr<DataBase::DbCrudBase>(new DataBase::DbCrud());

    std::string path = "../../project_2/data_base/";
    auto connector = std::unique_ptr<DataBase::DbConnectorBase>(new DataBase::DbConnector(path, crud));

    auto interaction = std::unique_ptr<Interaction::InteractionBase>(new Interaction::Interaction());

    Enviroment::Config::init(connector, interaction);

    auto init_db = Enviroment::Config::instance()->get_db_con()->init_db();

    if(init_db.has_error())
    {
        std::cerr << init_db.error() << std::endl;
    }
    
#pragma endregion

#pragma region UI
    
    UiMenu::MainMenu mainMenu;
    Fascades::UiFascade::showMenu(mainMenu);

#pragma endregion

    return EXIT_SUCCESS;
}