#include "db_create.h"

void HarshieCreateDatabase::languageData()
{
    try
    {
        database.createTable("language_config", "id TEXT, language TEXT");
        fmt::print("[{}] language_config table created!\n", dpp::utility::current_date_time());
    }
    catch(...)
    {
        fmt::print("[{}] Failed to create language_config table\n", dpp::utility::current_date_time());
    }
}
