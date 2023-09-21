/*
 * Copyright (C) 2023 harshfeudal
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see https://www.gnu.org/licenses/.
 */

#pragma once

#include <postgresql/libpq-fe.h>
#include <string>

class HarshieDatabase
{
private:
    PGconn* connection;
    HarshieDatabase();

public:
    ~HarshieDatabase();

    void connectDatabase(const std::string& connectionString);
    static HarshieDatabase& getInstance();

    bool createTable(const std::string& tableName, const std::string& columns);
    bool insertData(const std::string& tableName, const std::string& values);
    bool deleteData(const std::string& tableName, const std::string& condition);
    bool findRecord(const std::string& tableName, const std::string& searchCondition);
    std::string selectData(const std::string& targetColumn, const std::string& tableName, const std::string& searchCondition);

    HarshieDatabase(const HarshieDatabase&) = delete;
    HarshieDatabase(HarshieDatabase&&) = delete;
    HarshieDatabase& operator=(const HarshieDatabase&) = delete;
    HarshieDatabase& operator=(HarshieDatabase&&) = delete;
};
