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

#include "../../harshie.h"

void Harshie::HarshieLanguagesValue(const dpp::select_click_t& event)
{
    std::string setLanguage = "en-us";

    json& languagesJSON = HarshieLanguages::getInstance().getLanguagesJSON();
    HarshieDatabase& database = HarshieDatabase::getInstance();

    auto recordServerID = fmt::format("'{}'", event.command.guild_id);
    auto searchServer = database.findRecord("server_config", "id=" + recordServerID);

    if (searchServer)
        setLanguage = database.exportData("server_language", "server_config", "id=" + recordServerID);

    auto findDetails = languagesJSON["CONFIG_SERVER"][setLanguage]["select-menu"]["languages"];

    auto create_embed = dpp::embed()
        .set_title(findDetails["title"])
        .set_description(findDetails["description"])
        .set_color(0xabf2d3)
        .set_timestamp(time(0));

    event.reply(
        dpp::message().add_embed(create_embed).add_component(
            dpp::component().add_component(
                dpp::component()
                .set_type(dpp::cot_selectmenu)
                .set_placeholder("Choose language")
                .add_select_option(dpp::select_option("English", "en-us"))
                .add_select_option(dpp::select_option("Japanese", "ja-jp"))
                .set_id("server_language")
            )
        ).set_flags(dpp::m_ephemeral)
    );
}

void Harshie::HarshieLanguageSelection(const dpp::select_click_t& event)
{
    selectLanguage = event.values[0];
    HarshieDatabase& database = HarshieDatabase::getInstance();

    auto recordServerID = fmt::format("'{}'", event.command.guild_id);
    auto searchServer = database.findRecord("server_config", "id=" + recordServerID);

    std::string setLanguage = languageManager("server_config", selectLanguage, searchServer, recordServerID, database);

    json& languagesJSON = HarshieLanguages::getInstance().getLanguagesJSON();
    auto findDetails = languagesJSON["CONFIG_SERVER"][setLanguage]["select-menu"]["languages"]["language-menu"];

    auto create_embed = dpp::embed()
	    .set_title(findDetails["title"])
	    .set_color(0x38ff9b)
	    .set_description(findDetails["description"])
	    .set_timestamp(time(0));

    event.reply(
        dpp::message().add_embed(create_embed).set_flags(dpp::m_ephemeral)
    );
}
