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

// This file will be soon constructed!

#include "../cmd_lists.h"

void config_server(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    std::string setLanguage = "en-us";

    json& languagesJSON = HarshieLanguages::getInstance().getLanguagesJSON();
    HarshieDatabase& database = HarshieDatabase::getInstance();

    auto recordServerID = fmt::format("'{}'", event.command.guild_id);
    auto searchServer = database.findRecord("server_config", "id=" + recordServerID);

    if (searchServer)
        setLanguage = database.exportData("server_language", "server_config", "id=" + recordServerID);

    auto findDetails = languagesJSON["CONFIG_SERVER"][setLanguage];

    auto create_embed = dpp::embed()
        .set_title(findDetails["title"])
        .set_color(0xabf2d3)
        .set_timestamp(time(0))
        .add_field(findDetails["name-langs"], findDetails["description-langs"]);

    auto serverConfigSelection = dpp::component().add_component(
        dpp::component()
        .set_type(dpp::cot_selectmenu)
        .set_placeholder("Server Configuration")
        .add_select_option(
            dpp::select_option(
                "Server Languages",
                "languages",
                "Select server language for the bot when sending."
            )
        )
        .add_select_option(
            dpp::select_option(
                "Moderation",
                "moderation",
                "Moderation configuration."
            )
        )
        .set_id("server_config")
    );

    event.reply(
        dpp::message().add_embed(create_embed).add_component(serverConfigSelection)
    );
}
