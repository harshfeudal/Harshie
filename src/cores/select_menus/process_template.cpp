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

#include "process_template.h"

std::string languageManager(std::string tableName, std::string selectLanguage, bool searchAvailable, std::string recordID, HarshieDatabase& database)
{
    std::string setLanguage = "en-us";

    if (selectLanguage == "en-us")
    {
        if (searchAvailable)
            database.deleteData(tableName, "id=" + recordID);
    }
    else
    {
        if (selectLanguage == "ja-jp")
        {
            if (searchAvailable)
                database.deleteData(tableName, "id=" + recordID);

            setLanguage = "ja-jp";
        }
        else if (selectLanguage == "zn-cn")
        {
            if (searchAvailable)
                database.deleteData(tableName, "id=" + recordID);

            setLanguage = "zn-cn";
        }

        database.insertData(tableName, recordID + ", '" + setLanguage + "'");
    }

    return setLanguage;
}
