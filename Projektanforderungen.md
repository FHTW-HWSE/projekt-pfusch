# Requirements
* Functional Requriements
    * assign people with designated contact person to a table and time
    * set table free
    * add table using coordinates
    * delete table
    * save table
    * list all contact person around a specified reservation within a set perimeter and time frame
    * Use some form of database to store and modify information
* Non-Functional Requriements
    * no commercial use
    * no GUI
    * user interactions over text input using the terminal
    * no localization (exept time)
    * min 60% Unit-Test coverage (60% of code must be reached by tests)
    * Unit-Test-Framework using Catch2
    * gcc compiler
    * Use CMake to compile projects
    * Multiple running Instances on the same DB are not supported
        * No concurrency checks
* Constraints
    * project dead line 13.6.2023
    * project start 28.2.2023
    * no extra cost for licenses
    * Using C++ language
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
* **Given** the format of the reservation does not conform to accepted standards **When** a user wants to close a reservation **Then** an error message is displayed and the reservation is not saved.

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

* **Given** a valid table is selected **When** a user removes the table **Then** the table is removed from the DB and a success prompt is displayed.
* **Given** no table is selected **when** a user wants to remove a table **Then** the user gets an error prompt.
* **Given** no DB connection is possible **When** a user removes a table **Then** an error prompt is displayed.
* **Given** a DB error **When** a user adds a table **Then** an error prompt is displayed.

## DB add table
**As a** user **I want to** add a table into the DB **so that** I can store and access a layout of my restaurant

### Acceptance criteria
* **Given** a position **When** a user adds a table **Then** the table is stored in the DB.
* **Given** a table already exists at the given position **When** a user adds a table **Then** an error message is displayed.
* **Given** no position **When** a user adds a table **Then** an error prompt is displayed.
* **Given** no DB connection **When** a user adds a table **Then** an error prompt is displayed.
* **Given** a DB error **When** a user adds a table **Then** an error prompt is displayed.

## UI manage reservations

**As a** user **I want** to choose tables to allocate guests and be able to change the allocations **so that** I can manage the reservations.

### Acceptance criteria
* **Given** a UI element for managing reservations is implemented **When** a user selects this UI element **Then** they are prompted to select a table for allocation of a guest.
* **Given** a selected table is unoccupied **When** a user selects this table for allocation **Then** they get prompted to input guest details.
* **Given** a selected table is occupied **When** a user selects this table for allocation **Then** an error message is displayed and they get brought back to the menu for selecting a table.
* **Given** a table can be allocated guests **When** the user inputs guest details **Then** the details get saved to the database.
* **Given** incorrect details are input (i.e. wrong format, etc.) **When** the user tries to create the reservation **Then** an error message is displayed and they get brought back to the menu for inputting the details.

## UI close reservation
**As a** user I **want to** close a open reservation from a table **so that** this table can be used again

### Acceptance criteria
* **Given** the close reservation option was selected **when** a user closes a reservation **then** the user is prompted for the table.
* **Given** a table that has an active reservation **When** a user closes the reservation **Then** the reservation is closed, a success prompt is displayed and the current UI closes.
* **Given** no position or some invalid input **When** a user closes a reservation **then** an error prompt is displayed.
* **Given** an internal error **when** a user closes a reservation **then** an error prompt is displayed.

## UI add table
**As a** user **I want** add a table **so I** can configure the layout of the restaurant.

### Acceptance criteria
* **Given** the add table option was chosen **when** a user lands on the add table UI **then** the user is prompted for the position of the table.
* **Given** a valid position and capacity **when** a user adds a table **then** the table is added to the configuration, saved in the DB and the add table UI closes.
* **Given** a position where a table already exists **when** a user adds a table **then** an error prompt is displayed.
* **Given** no position **when** a user adds a table **then** an error prompt is displayed.
* **Given** an internal error **when** a user adds a table **then** an error prompt is displayed.

## UI configure tables Menu
**As a** user **I want** to have a configure tables UI **so that** I can add, remove, list all tables, list all available tables, list all reserved tables, list all reservations within a radius and time or exit the menu.

### Acceptance criteria
* **Given** a running program **when** the configure tables option has been chosen **then** the configure tables options are displayed.
* **Given** the configure tables UI **when** the add option has been chosen **then** the add table UI is displayed.
* **Given** the configure tables UI **when** the remove option has been chosen **then** the remove UI is displayed.
* **Given** the configure tables UI **when** the list all tables option is chosen **then** all tables are listed in the UI.
* **Given** there are no tables **when** the list all tables option is chosen **then** a prompt "empty list" is displayed.
* **Given** there are no available tables **when** the list all available tables option is chosen **then** a prompt "empty list" is displayed.

## UI configure reservations


### Acceptance critera

* **Given** the configure add reservations UI **when** the add option has been chosen **then** the add reservation UI is displayed.
* **Given** the configure remove reservations UI **when** the remove option has been chosen **then** the remove reservation UI is displayed.
* **Given** the configure reservations UI **when** the list all open reservations option is chosen **then** all open reservations are listed in the UI.
* **Given** the configure reservations UI **when** the list all reservations option is chosen **then** all reservations are listed in the UI.
* **Given** there are no reservations **when** the list all reservations option is chosen **then** a prompt "empty list" is displayed.
* **Given** the configuration reservations UI **when** an invalid option is chosen **then** an error prompt is displayed.
* **Given** the the configuration reservations UI **when** the list all reservations within a radius option is chosen **then** the user is forwarded to the list all reservations within a radius and time UI.
* **Given** any option is chosen and no DB connection is available **when** an option is chosen **then** an error prompt is displayed.
* **Given** the exit option is chosen **when** a user wants to exit the menu **then** the configure tables UI is closed.
* **Given** the configure tables UI **when** the list all available tables option is chosen **then** all available tables are listed in the UI.

## UI landing page menu

**As a** user **I want** a UI landing page **so that** I choose to either configure the tables, configure reservations or exit the program.

### Acceptance criteria
* **Given** the program **when** the program is instantiated **then** the UI landing page is displayed.
* **Given** the program **when** the landing page is displayed **then** a options to either configure tables, configure reservations or exit program can be selected.
* **Given** the configure reservations option is selected **when** the user wants configure the reservations **then** then the user gets forwarded to the configure reservations UI.
* **Given** the configure tables option is selected **when** the user wants to configure tables **then** then the user gets forwarded to the configure tables UI.
* **Given** the landing page **when** when the exit option is chosen **then** the program terminates.
* **Given** the landing page **when** an invalid option is chosen **then** an error prompt is displayed.

## DB realization
**As a** user **I want** to store and access the data in a .csv files **so that** i can store and access historical reservations data.

### Acceptance criteria

* **Given** a configue Reservations UI **when** a reservation is closed **then** the data is stored in a .csv file
* **Given** no reservations are stored in the database **When** a user tries to print out reservations (of a specific day or all reservations) **Then** the user gets  a prompt empty list.
* **Given** the format of the table does not conform to accepted standards (i.e. corruption, input error, etc.) **When** a user tries to save reservations to the database **Then** an error message is displayed.
* **Given** the format of the reservations does not conform to accepted standards (i.e. file corruption, etc.) **When** a user tries to access reservations from the database **Then** an error message is displayed.
* **Given** no reservations are stored in the database **When** a user tries to access reservations from the database **Then** prompt empty list.
* **Given** the specified reservation is not store in the database **When** a user tries to access this specific reservation **Then** an error message is displayed.

## list all reservations within radius and time of table
**As a** user **I want** to be able to list reservations at a given time and within at certain distance of a table **so that** I can check which tables I can notify.

### Acceptance criteria
* **Given** select a reservation **When** a user wants to list all reservations within radius and time interall **Then** all reservations in the radius and time intervall are listed in and the UI closes.
* **Given** no other reservation for the given reservation  **When** a user wants to list all reservations **Then** the user gets an  prompt empty list.
* **Given** no reservation or radius **when** a user wants to list all reservations **then** an error prompt is displayed and the UI closes.
* **Given** an internal error **when** a user wants to list all reservations **then** an error prompt is displayed and the UI closes.
* **Given** some invalid input **when** a user wants to list all reservations **then** an error prompt is displayed and the UI closes.
* **Given** no DB connection **When** a user wants to list all reservations **Then** an error is returned.
* **Given** invalid parameters **When** a user wants to list all reservations **Then** an error is returned.