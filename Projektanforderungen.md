# Requirements
* Functional Requriements
    * assign people with designated contact person to a table and time
    * set table free using coordinates and time
    * add table using coordinates and load limit
    * delete table using coordinates
    * save table with current config
    * list all used tables with contact person around a specified table within a set perimeter and time frame
    * Use some form of database to store and modify information
* Non-Functional Requriements
    * no commercial use
    * no GUI
    * user interactions over text input using the terminal
    * no localization 
    * min 60% Unit-Test coverage (60% of code must be reached by tests)
    * Unit-Test-Framework using Catch2
    * gcc compiler
    * Use CMake to compile project
    * Code documentation using Doxygen
    * feature will be developed in separate feature branches
    * TDD
    * Multiple running Instances on the same DB are not supported
        * No concurrency checks
* Constraints
    * project dead line 13.6.2023
    * project start 28.2.2023
    * no extra cost for licenses
    * Using C language
    * Project versioning using GitHub
    * Project management using GitHub (milestones, user stories, ect.)
    * Agile development using scrum in a 1 week sprint length
    * program runs locally under LINUX
    * No automatic roll-outs and updates
    * no budget, development hours are free of cost
    * commits to master using pull requests


# User Stories

## DB close reservation
**As a** user **I want** to be able to close a reservation **so that** that data can be stored in the db and a new reservation can be created

### Acceptance criteria
* **Given** a reservation is edited **When** a user wants to close it without a contact person **Then** the user gets an error prompt
* **Given** a reservation is edited **When** the reservation is finished **Then** at least an email address has to be set up
* **Given** the database has been successfully configured **When** a user closes a reservation **Then** the reservation gets saved to the database.
* **Given** the network connection is lost **When** a user closes a reservation **Then** an error message is displayed, that the reservation could not be changed.
* **Given** the format of the reservation does not conform to accepted standards **When** a user closes a reservation **Then** an error message is displayed and the reservation is not saved.

## DB add reservation
**As a** user **I want** to be able to add a reservation to the program **so that** I can update the restaurant's capacity and ensure accurate table availability.

### Acceptance criteria

* **Given** a table is chosen and a contact person is provided **When** a user creates a reservation **Then** the reservation is saved to the DB.
* **Given** not all parameters are provided **When** a user creates a reservation **Then** an error prompt is displayed.
* **Given** a not existing table is chosen **When** a user creates a reservation **Then** an error prompt is displayed.
* **Given** no DB connection is possible **When** a user creates a reservation **Then** an error prompt is displayed.
* **Given** a DB error **When** a user adds a table **Then** an error prompt is displayed.

## DB remove table
**As a** user **I want** to be able to remove a table from the database **so that** I can update the restaurant's capacity and ensure accurate table availability.

### Acceptance criteria

* **Given** the chosen table ha an active reservation **When** the table is removed **Then** the user gets an error prompt message indicating that table has an active reservation.
* **Given** a valid position of a table **When** a user removes the table **Then** the table is removed from the DB and a success prompt is displayed.
* **Given** no position of an table **when** a user wants to remove a table **Then** the user gets an error prompt.
* **Given** a not existing table is chosen **When** a user removes a table **Then** an error prompt is displayed.
* **Given** no DB connection is possible **When** a user removes a table **Then** an error prompt is displayed.
* **Given** a DB error **When** a user adds a table **Then** an error prompt is displayed.

## DB add table
**As a** user **I want to** add a table into the DB **so that** I can store and access a layout of my restaurant

### Acceptance criteria
* **Given** a position and the capacity **When** a user adds a table **Then** the table is stored in the DB.
* **Given** a table already exists at the given position **When** a user adds a table **Then** an error message is displayed.
* **Given** no position or capacity is provided **When** a user adds a table **Then** an error prompt is displayed.
* **Given** no DB connection **When** a user adds a table **Then** an error prompt is displayed.
* **Given** a DB error **When** a user adds a table **Then** an error prompt is displayed.

## UI manage reservations

**As a** user **I want** to choose tables to allocate guests and be able to change the allocations **so that** I can manage the reservations.

### Acceptance criteria
* **Given** a UI element for managing reservations is implemented **When** a user selects this UI element **Then** they are prompted to select a table for allocation of a guest.
* **Given** a selected table is unoccupied **When* a user selects this table for allocation **Then** they get prompted to input guest details.
* **Given** a selected table is occupied **When** a user selects this table for allocation **Then** an error message is displayed and they get brought back to the menu for selecting a table.
* **Given** a table can be allocated guests **When** the user inputs guest details **Then** the details get saved to the database.
* **Given** the network connection is lost **When** the user inputs guest details **Then** an error message is displayed.
* **Given** incorrect details are input (i.e. wrong format, etc.) **When** the user tries to complete the reservation **Then** an error message is displayed and they get brought back to the menu for inputting the details.
* **Given** a guest has been successfully allocated a table **When** a user selects the UI element to change the reservation to a different table **Then** the reservation is copied to the selected table (if unoccupied) and removed from the current table.
* **Given** the new table is currently occupied **When** a user tries to change a reservation to this table **Then** an error message is displayed and they get brought back to the menu for table selection.
* **Given** the table, from which the reservation should be changed to a different table, is empty **When** a user tries to change the reservation from this table **Then** an error message is displayed.

## UI close business day
**As a** user **I want** to close a business day **so that** no changes and interactions can be performed after the day ends.

### Acceptance criteria
* **Given** the UI element for closing the business day is implemented **When** a user selects the UI element for closing the business day **Then** no further input can be given to the programme.
* **Given** the UI element for closing the business day has been selected **When** the selection has been confirmed and all interactions prevented **Then** the current state of the business day is saved to the database.
* **Given** The database connection is lost **When** a user confirmes the closing of a business day (and the current state should be saved tot the database) **Then** an error message is displayed.
* **Given** the UI element for closing the business day has been selected **When** a user does not confirm the selection **Then** an error/abortion message is displayed.

## UI start business day
**As a** user **I want** to start a business day **so that** I can start managing the reservations for the restaurant.

### Acceptance criteria
* **Given** The "start business day" was selected **When** a user lands at the start a business day UI **Then** the user is prompted for a date.
* **Given** a date is provided **When** a user starts a business day **Then** a new start for the day is saved if no such entry already exists and the user is forwarded to the manage reservations UI.
* **Given** The "start business day" was selected and no date or invalid input was provided **When** a user starts a business day **Then** an error prompt is displayed.
* **Given** a valid date is provided and no DB connection exists **when** a user starts a business day **then** an error prompt is displayed.

## UI close reservation
**As a** user I **want to** close a reservation from a table **so that** this table can be used again

### Acceptance criteria
* **Given** the close reservation option was selected **when** a user closes a reservation **then** the user is prompted for the table position.
* **Given** the position of a table that has an active reservation **When** a user closes the reservation **Then** the reservation is closed, a success prompt is displayed and the current UI closes.
* **Given** the position of a table that has no active reservation **When** a user closes the reservation **Then** An error prompt is displayed.
* **Given** no position or some invalid input **When** a user closes a reservation **then** an error prompt is displayed.
* **Given** an internal error **when** a user closes a reservation **then** an error prompt is displayed.

## UI add table
**As a** user **I want** add a table **so I** can configure the layout of the restaurant.

### Acceptance criteria
* **Given** the add table option was chosen **when** a user lands on the add table UI **then** the user is prompted for the position and capacity of the table.
* **Given** a valid position and capacity **when** a user adds a table **then** the table is added to the configuration, saved in the DB and the add table UI closes.
* **Given** a position where a table already exists **when** a user adds a table **then** an error prompt is displayed.
* **Given** no position or capacity **when** a user adds a table **then** an error prompt is displayed.
* **Given** an internal error **when** a user adds a table **then** an error prompt is displayed.

## UI configure tables Menu
**As a** user **I want** to have a configure tables UI **so that** I can add, remove, list all tables, list all available tables, list all reserved tables, list all reservations within a radius and time or exit the menu.

### Acceptance criteria
* **Given** a running program **when** the configure tables option has been chosen **then** the configure tables options are displayed.
* **Given** the configure tables UI **when** the add option has been chosen **then** the add table UI is displayed.
* **Given** the configure tables UI **when** the remove option has been chosen **then the remove UI is displayed.
* **Given** the configure tables UI **when** the list all tables option is chosen **then** all tables are listed in the UI.
* **Given** there are no tables **when** the list all tables option is chosen **then** a prompt "empty list" is displayed.
* **Given** the configure tables UI **when** the list all available tables option is chosen **then** all available tables are listed in the UI.
* **Given** there are no available tables **when** the list all available tables option is chosen **then** a prompt "empty list" is displayed.
* **Given** the configure tables UI **when** the list all reserved tables option is chosen **then** all reserved tables are listed in the UI.
* **Given** there are no reserved tables **when** the list all reserved tables option is chosen **then** a prompt "empty list" is displayed.
* **Given** the configure tables UI and no table configuration exists **when** the list option is chosen **then** an error prompt is displayed.
* **Given** the configuration tables UI **when** an invalid option is chosen **then** an error prompt is displayed.
* **Given** the the configuration tables UI **when** the list all reservations within a radius and time option is chosen **then** the user is forwarded to the list all reservations within a radius and time UI.
* **Given** any option is chosen and no DB connection is available **when** an option is chosen **then** an error prompt is displayed.
* **Given** the exit option is chosen **when** a user wants to exit the menu **then** the configure tables UI is closed.

## UI landing page menu

**As a** user **I want** a UI landing page **so that** I choose to either configure the tables, start a business day or exit the program.

### Acceptance criteria
* **Given** the program **when** the program is instantiated **then** the UI landing page is displayed.
* **Given** the program **when** the landing page is displayed **then** a options to either configure the tables or start a business day can be selected.
* **Given** the start business day option is selected **when** the user wants to start the day **then** then the user gets forwarded to the start business day UI.
* **Given** the start manage tables option is selected **when** the user wants to start the day **then** then the user gets forwarded to the start business day UI.
* **Given** the landing page **when** when the exit option is chosen **then** the program terminates.
* **Given** the landing page **when** an invalid option is chosen **then** an error prompt is displayed.

## DB realization
**As a** user **I want** to store and access the data for each day in a .csv files **so that** i can store and access historical data.

### Acceptance criteria

* **Given** a new day/date starts **when** a reservation is closed **then** the data is stored in a .csv file
* **Given** the restaurant closes **when** a user wants to adjust a reservation **then** he gets an error prompt
* **Given** a new day starts/restaurant opens **when** no .csv file is created **then** an error prompt appears
* **Given** reservations are stored in the database **When** a user wants to print out a list of reservations **Then** the reservations are copied from the database into a .csv-file.
* **Given** a business day has been completed and all reservations accordingly saved **When** a user wants to print out a specific reservation from that day **Then** the reservation is copied from the database into a .csv-file.
* **Given** no reservations are stored in the database (for a certain day or in general) **When** a user tries to print out reservations (of a specific day or all reservations) **Then** an error message is displayed.
* **Given** the format of the reservations does not conform to accepted standards (i.e. corruption, input error, etc.) **When** a user tries to save reservations to the database **Then** an error message is displayed.
* **Given** the format of the reservations does not conform to accepted standards (i.e. file corruption, etc.) **When** a user tries to access reservations from the database **Then** an error message is displayed.
* **Given** no reservations are stored in the database **When** a user tries to access reservations from the database **Then** an error message is displayed.
* **Given** the specified reservation is not store in the database **When** a user tries to access this specific reservation **Then** an error message is displayed and he gets redirected to select a different reservation.

## list all reservations within radius and time of table
**As a** user **I want** to be able to list reservations at a given time and within at certain distance of a table **so that** I can check which tables I can notify.

### Acceptance criteria
* **Given** a position, time and distance **When** a user wants to list all reservations **Then** all reservations are listed in and the UI closes.
* **Given** no reservation for the given position and time **When** a user wants to list all reservations **Then** the user gets an error prompt and the UI closes.
* **Given** no position or time or radius **when** a user wants to list all reservations **then** an error prompt is displayed and the UI closes.
* **Given** an internal error **when** a user wants to list all reservations **then** an error prompt is displayed and the UI closes.
* **Given** some invalid input **when** a user wants to list all reservations **then** an error prompt is displayed and the UI closes.
* **Given* no DB connection **When** a user wants to list all reservations **Then** an error is returned.
* **Given** no DB entry for the day **When** a user wants to list all reservations **Then** an error is returned.
* **Given** invalid parameters **When** a user wants to list all reservations **Then** an error is returned.