/***
* This handles all the connections and function for working with the database
* Such as the CRUD functions
***/
#pragma once
#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>


class SqlDriver{
    private:

    std::string USERNAME;
    std::string PASSWORD;

    // Variables to connect to database
    protected:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    public:
    bool InitConnection();
    void quitApplication();
    void createItem();
    void updateItem();
    void deleteItem();
    void displayItems();
    void setCredentials();
    void mainMenu();
    bool validateInput(std::string);
    bool validateDecimal(std::string);
    std::string toLower(std::string);


};
