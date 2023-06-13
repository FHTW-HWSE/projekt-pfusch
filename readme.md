# Project pfusch

## external dependencies

This project uses a git submodule to as external dependency. It is required to init and pull this submodule.

Furthermore Catch2 version 3, CMake version 3.10.0 and C++ version 20 must be installed on the computer. 

The project is developed under Linux Debian and is meant to only be executed in a Debian enviroment.

# internal dependencies

The folder *data_base* must exist in *project_2/*. 

The folder "db_source" must exist in *project_2/test/*.

# build using CMake

Cmake will create 2 executables. *p2* is the live executable that can be run in the terminal. The second executable is called *project_2_test* and runs some unit tests and some integration tests.

# how to use executable *ps*

Build the project and execute the *p2*. On Startup the program will initialize the data base. After sucessfull initialization the user is greeted with a welcome message. 

A user can navigate the program using the terminal. Whenever some input is required, the user is prompted for input. Simply provide the data by writing into the terminal.

Whenever there is an error, the user is notified with a message on what went wrong.

# how to use *project_2_test*

Build the project and execute *project_2_test*. The unit tests and integration tests execute automatically and the result is provided in the terminal.

# development process

This project is written by *Robert Castillo* and *Sebastian Rath*. We used an agile prozess with weekly sprints to allocate the workload and synchronize the team. 

The project is devided into 3 main parts:
- enviroment
- data base
- ui

These parts allowed us to segregate the project into distinct parts which are only loosly coupled together. Each part exposes an interface and hides the actual implementation.  