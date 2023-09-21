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

#include <fstream>

#include <nlohmann/json.hpp>

#include "../cmd_lists.h"

using json = nlohmann::json;

void config_language(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    const auto selectLanguage = std::get<std::string>(event.get_parameter("language"));
    HarshieDatabase& database = HarshieDatabase::getInstance();

    auto recordUser = fmt::format("'{}'", event.command.usr.id);
    auto searchUser = database.findRecord("language_config", "id=" + recordUser);

    std::string setLanguage = "en-us";

    if (selectLanguage == "english")
    {
        if (searchUser)
            database.deleteData("language_config", "id=" + searchUser);
    }
    else if (selectLanguage == "japanese")
    {
        if (searchUser)
            database.deleteData("language_config", "id=" + searchUser);

        setLanguage = "ja-jp";
        database.insertData("language_config", searchUser + ", '" + setLanguage + "'");
    }

    json languagesJSON;

    std::ifstream openLanguagesFile("languages.json");
    openLanguagesFile >> languagesJSON;

    auto embedDescription = languagesJSON["CONFIG_LANGUAGE"][setLanguage];
    
    auto create_embed = dpp::embed()
	    .set_title(embedDescription["title"])
	    .set_color(0x38ff9b)
	    .set_description(embedDescription["description"])
	    .set_timestamp(time(0));

    event.reply(dpp::message().add_embed(create_embed).set_flags(dpp::m_ephemeral));
}
