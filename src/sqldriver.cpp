#include "../include/sqldriver.h"

#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cctype>


/// Initialize connection to database
bool SqlDriver::InitConnection(){

    // Get users credentials
    setCredentials();
    // Check for validity
    try {
        // Create a driver instance
        driver = sql::mysql::get_mysql_driver_instance();

        // Connect to the local database
        con = driver->connect("tcp://localhost:3306", USERNAME, PASSWORD);

    }
    catch (...) {
        std::cout << "Error: " <<  "Could not connect to database. Incorrect username or password." << std::endl;
        return false;
    }

    // If connected to the database successfully
    if (con->isValid()){

        stmt = con->createStatement();

        try{
            std::cout << "Connecting...." << std::endl;
            con->setSchema("Inventory");
            std::cout << "Connected to the database Inventory Successfully!" << std::endl;
            return true;
        }

        //  Create a new database and table if it does not exists
        catch(...){
            stmt->execute("CREATE DATABASE Inventory");
            con->setSchema("Inventory");
            std::cout << "Creating table...." << std::endl;
            stmt->execute("CREATE TABLE Items(ItemId int NOT NULL AUTO_INCREMENT, Name varchar(255) NOT NULL, Quantity int NOT NULL, Price double NOT NULL, PRIMARY KEY(ItemId), UNIQUE (Name));");
            std::cout << "Database Inventory and Table Items created successfully!" << std::endl;
        }

    }
    return true;
}

/// Gets credential from user
void SqlDriver::setCredentials(){
    std::cout << "Enter username: ";
    std::cin >> USERNAME;
    std::cout << "Enter password: ";
    std::cin >> PASSWORD;
}


/// Main Menu of the application
void SqlDriver::mainMenu(){

    bool quit = false;
    bool validInput = false;
    std::string menuChoice = "";

    // Connnect to database until connection successful
    while(!InitConnection()){
    }

    // Main loop
    while(!quit){
        std::cout << std::endl;
        std::cout << "1. Display Items" << std::endl;
        std::cout << "2. Create Item" << std::endl;
        std::cout << "3. Update Item" << std::endl;
        std::cout << "4. Delete Item" << std::endl;
        std::cout << "5. Quit" << std::endl;


        std::cout << "\n\nEnter choice: ";
        std::cin >> menuChoice;
        std::cout << std::endl;

        // Validate input
        validInput = validateInput(menuChoice);

        // If input is number
        if(validInput){
            // Convert input into int
            int num = std::stoi(menuChoice);
            switch(num){
                case 1: displayItems();
                        break;
                case 2: createItem();
                        break;
                case 3: updateItem();
                        break;
                case 4: deleteItem();
                        break;
                case 5: quitApplication();
                        quit = true;
                        break;
                default: std::cout << "Incorrect choice!" << std::endl;
                        break;
            }
        }
        else{
            std::cout << "Invalid choice!" << std::endl;
            std::cin.clear();
            menuChoice = "";
        }
    }

}


/// Display the items in the database
void SqlDriver::displayItems(){

}

/// Create a new item in the database
void SqlDriver::createItem(){
        std::string name;
        std::string qty;
        std::string price;

        std::cout << "Enter name: ";
        std::cin >> name;
        std::cout << "Enter quantity: ";
        std::cin >> qty;
        std::cout << "Enter price: ";
        std::cin >> price;

        name = toLower(name);

        if(validateInput(qty)){
            std::string insertString = "INSERT INTO Items (Name, Quantity, Price) VALUES ('" + name + "'" +  ", " + qty + ", " + price + ");";

            try{
                stmt->execute(insertString);
            }
            catch(...){
                std::cout << "Item already exists" << std::endl;
            }
        }
}

/// Update and item from the database
void SqlDriver::updateItem(){

}

/// Delete item from the database
void SqlDriver::deleteItem(){

}

/// Deletes the connection to free up memory, and exits the application
void SqlDriver::quitApplication(){

    std::cout << "Quitting...." << std::endl;
    delete con;
    delete stmt;
}


/// Converts string to lower case
std::string SqlDriver::toLower(std::string name){
    std::string lowerName = "";
    for(char letter : name){
        lowerName += tolower(letter);
    }
    return lowerName;
}

/// Validate if user inpu is decimal
bool SqlDriver::validateDecimal(std::string str){
    bool result;
    int periodCount = 0;

    for(letter : str){

        if((letter == '.' && periodCount < 1) || isdigit(letter)){
            result = true;
        }
        else{
            result = false;
        }

    }
    return result;
}

/// Validate if user input is digit
bool SqlDriver::validateInput(std::string str){
    bool result;

    for(char letter : str){

        // Check if the char is a digit
        if(isdigit(letter)){
            result = true;
        }
        else{
            result = false;
        }
    }

    return result;
}
