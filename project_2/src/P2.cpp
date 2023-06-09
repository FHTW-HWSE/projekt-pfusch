#include "Base.hpp"
#include "Enviroment.hpp"
#include "DbConnector.hpp"
#include "DbCrud.hpp"
#include "DbFascade.hpp"
#include "UiFascade.hpp"
#include <iostream>
#include "UIMainMenu.hpp"

int main(int argc, char* args[])
{
#pragma region init enviroment
    auto crud = std::unique_ptr<DataBase::DbCrudBase>(new DataBase::DbCrud());

    std::string path = "../../project_2/test/db_source/";
    auto connector = std::unique_ptr<DataBase::DbConnectorBase>(new DataBase::DbConnector(path, crud));

    Enviroment::Config::init(connector);

    auto init_db = Enviroment::Config::instance()->get_db_con()->init_db();

    if(init_db.has_error())
    {
        std::cerr << init_db.error() << std::endl;
    }
#pragma endregion
    
    UiMenu::MainMenu mainMenu;
    auto mainMenu_r = Fascades::UiFascade::showMenu(mainMenu);

    // auto write_string_r = Fascades::UiFascade::write_string("input an integer.");

    // if(write_string_r.has_error())
    // {
    //     std::cerr << write_string_r.error() << std::endl;
    // }

    // auto get_int_r = Fascades::UiFascade::get_int();

    // if(get_int_r.has_error())
    // {
    //     std::cerr << get_int_r.error() << std::endl;
    // }

    // int user_int = get_int_r.value();

    // std::vector<std::string> options;
    // options.push_back("opt 1");
    // options.push_back("opt 2");
    // options.push_back("opt 3");

    // std::string opt_header = "please select an option.";
    // auto get_option = Fascades::UiFascade::print_options_and_get_result(options, opt_header);

    // if(get_option.has_error())
    // {
    //     std::cerr << get_option.error() << std::endl;
    // }

    // Entities::TableEntity table1(0,0,0);
    // auto create_table = Fascades::DbFascade::create_table(table1);

    // if(create_table.has_error())
    // {
    //     std::cerr << "could not create table." << std::endl << create_table.error() << std::endl;
    // }

    // std::vector<std::unique_ptr<Entities::TableEntity>> tables;
    // auto read_table = Fascades::DbFascade::get_tables_by_id(tables, table1.id);

    // if(read_table.has_error())
    // {
    //     std::cerr << read_table.error() << std::endl;
    // }

    return EXIT_SUCCESS;
}