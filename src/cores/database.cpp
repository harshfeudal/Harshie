#include <stdexcept>
#include <cstdlib>

#include "database.h"

HarshieDatabase::HarshieDatabase(const std::string& connectionString)
{
    connection = PQconnectdb(connectionString.c_str());
    if (PQstatus(connection) != CONNECTION_OK)
    {
        throw std::runtime_error("Connection to the database failed: " + std::string(PQerrorMessage(connection)));
    }
}

HarshieDatabase::~HarshieDatabase()
{
    PQfinish(connection);
}

bool HarshieDatabase::createTable(const std::string& tableName, const std::string& columns)
{
    std::string query = "CREATE TABLE IF NOT EXISTS " + tableName + " (" + columns + ");";
    PGresult* result = PQexec(connection, query.c_str());
    ExecStatusType status = PQresultStatus(result);
    PQclear(result);

    return status == PGRES_COMMAND_OK;
}

bool HarshieDatabase::insertData(const std::string& tableName, const std::string& values)
{
    std::string query = "INSERT INTO " + tableName + " VALUES (" + values + ");";
    PGresult* result = PQexec(connection, query.c_str());
    ExecStatusType status = PQresultStatus(result);
    PQclear(result);

    return status == PGRES_COMMAND_OK;
}

bool HarshieDatabase::deleteData(const std::string& tableName, const std::string& condition)
{
    std::string query = "DELETE FROM " + tableName + " WHERE " + condition + ";";
    PGresult* result = PQexec(connection, query.c_str());
    ExecStatusType status = PQresultStatus(result);
    PQclear(result);

    return status == PGRES_COMMAND_OK;
}

int HarshieDatabase::getCount(const std::string& tableName, const std::string& searchCondition)
{
    std::string query = "SELECT COUNT(*) FROM " + tableName + " WHERE " + searchCondition + ";";
    PGresult* result = PQexec(connection, query.c_str());

    if (PQresultStatus(result) == PGRES_TUPLES_OK)
    {
        int count = atoi(PQgetvalue(result, 0, 0));
        PQclear(result);
        return count;
    }
    else
    {
        PQclear(result);
        throw std::runtime_error("Error executing query: " + query);
    }
}

std::string HarshieDatabase::selectData(const std::string& targetColumn, const std::string& tableName, const std::string& searchCondition)
{
    std::string query = "SELECT " + targetColumn + " FROM " + tableName + " WHERE " + searchCondition + ";";
    PGresult* result = PQexec(connection, query.c_str());

    if (PQresultStatus(result) == PGRES_TUPLES_OK)
    {
        std::string data = PQgetvalue(result, 0, 0);
        PQclear(result);
        return data;
    }
    else
    {
        PQclear(result);
        throw std::runtime_error("Error executing query: " + query);
    }
}
