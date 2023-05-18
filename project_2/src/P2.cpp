#include <stdio.h>
#include <iostream>

#include "Base.hpp"
#include "DbConnector.hpp"

int main(int argc, char* args[]){

    std::string connection = "./";
    DataBase::DbConnector::init_connector(connection);

    auto r_db_structure = DataBase::DbConnector::instance()->init_db_structure();

    if(r_db_structure.has_error()){
        std::cout << r_db_structure.error() << std::endl;
    }
    else{
        std::cout << "fuck yeah" << std::endl << DataBase::DbConnector::instance()->get_connection_string() << std::endl ;
    }

    return EXIT_SUCCESS;
}