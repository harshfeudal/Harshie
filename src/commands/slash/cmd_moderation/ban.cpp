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

#include "../cmd_lists.h"
#include "../cmd_validation.h"
#include "../cmd_decoration.h"

void ban(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    const auto userID = std::get<dpp::snowflake>(event.get_parameter("user"));
    const auto guildID = event.command.guild_id;

	const auto getGuild = dpp::find_guild(guildID);
	const auto getUser = getGuild->members.find(userID);

	std::string selectLanguage = "en-us";
	HarshieDatabase& database = HarshieDatabase::getInstance();

	auto recordServerID = fmt::format("'{}'", event.command.guild_id);
    auto searchServer = database.findRecord("server_config", "id=" + recordServerID);

    if (searchServer)
        selectLanguage = database.exportData("server_language", "server_config", "id=" + recordServerID);

    json& languagesJSON = HarshieLanguages::getInstance().getLanguagesJSON();
    auto findBanDetails = languagesJSON["BAN"][selectLanguage]["server-language"];

	const auto isValidate = cmndValidation(client, event, userID, dpp::p_ban_members, findBanDetails["ban"]);

	if (!std::get<bool>(isValidate))
	{
		const auto reasonParam = event.get_parameter("reason");
		const auto reason = std::holds_alternative<std::string>(reasonParam)
			? std::get<std::string>(reasonParam)
			: findBanDetails["no-reason"];

		dpp::user user = client.user_get_sync(userID);
		bool isBannedBefore = false;

		try
		{
			client.guild_get_ban_sync(guildID, userID);
			isBannedBefore = true;

			std::string description = fmt::format(findBanDetails["is-banned-before"], user.format_username());
			sendErrorEmbed(selectLanguage, description, event);
		}
		catch (...) {}

		if (!isBannedBefore)
		{
			client.set_audit_reason(reason);
			client.guild_ban_add(guildID, userID);

			std::string description = fmt::format(findBanDetails["description"], user.format_username());

			if (getUser == getGuild->members.end())
				description = fmt::format(findBanDetails["not-in-server"], user.format_username());

			sendSucessfulEmbed(selectLanguage, description, event);
		}
	}
}
