#pragma once

#include <postgresql/libpq-fe.h>
#include <string>

class HarshieDatabase
{
private:
    PGconn* connection;

public:
    HarshieDatabase(const std::string& connectionString);
    ~HarshieDatabase();

    bool createTable(const std::string& tableName, const std::string& columns);
    bool insertData(const std::string& tableName, const std::string& values);
    bool deleteData(const std::string& tableName, const std::string& condition);
    int getCount(const std::string& tableName, const std::string& searchCondition);
    std::string selectData(const std::string& targetColumn, const std::string& tableName, const std::string& searchCondition);
};
