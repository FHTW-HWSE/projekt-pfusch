// #define CATCH_CONFIG_MAIN
// #define DO_NOT_USE_WMAIN
// #include <catch2/catch.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string>
#include <cstdio>
#include <fstream>

#include "MainTest.hpp"
#include "test.hpp"
#include "Enviroment.hpp"
#include "DbConnectorMock.hpp"
#include "DbCrudMock.hpp"
#include "DbConnector.hpp"
#include "DbCrud.hpp" 
#include "InteractionMock.hpp"
#include "Interaction.hpp"

// Standard C/C++ main entry point
const std::string DB_PATH = "../../project_2/test/db_source/";

int main( int argc, char* argv[] ) 
{
  // your setup ...

  Enviroment_mock();

  int result = Catch::Session().run( argc, argv );

  // your clean-up...

  return result;
}

void drop_db()
{
  std::string table_path = Enviroment::Config::instance()->get_db_con()->get_table_layout_path().value();
  std::string reservation_path = Enviroment::Config::instance()->get_db_con()->get_reservation_path().value();

  std::remove(table_path.c_str());
  std::remove(reservation_path.c_str());
}

void clear_db()
{
  std::string table_path = Enviroment::Config::instance()->get_db_con()->get_table_layout_path().value();
  std::string reservation_path = Enviroment::Config::instance()->get_db_con()->get_reservation_path().value();

  try
  {
    std::ofstream ofs;
    ofs.open(table_path, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
  }
  catch(const std::exception& e)
  {
    
  }
  
  try
  {
    std::ofstream ofs;
    ofs.open(reservation_path, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
  }
  catch(const std::exception& e)
  {
    
  }
}

void Enviroment_mock()
{
  auto crud = std::unique_ptr<DataBase::DbCrudBase>(new DataBase::DbCrudMock());

  std::string path = "./db_source/";
  auto connector = std::unique_ptr<DataBase::DbConnectorBase>(new DataBase::DbConnectorMock(path, crud));
  
  auto inter = std::unique_ptr<Interaction::InteractionBase>(new Interaction::InteractionMock());

  Enviroment::Config::init(connector, inter);
}

void Enviroment_actual()
{
  auto crud = std::unique_ptr<DataBase::DbCrudBase>(new DataBase::DbCrud());

  std::string path = "./db_source/";
  auto connector = std::unique_ptr<DataBase::DbConnectorBase>(new DataBase::DbConnector(path, crud));

  auto inter = std::unique_ptr<Interaction::InteractionBase>(new Interaction::Interaction());

  
  Enviroment::Config::init(connector, inter);
}
