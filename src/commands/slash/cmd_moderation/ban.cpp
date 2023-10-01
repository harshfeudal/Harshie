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

// Under-construction!

void ban(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    const auto userID = std::get<dpp::snowflake>(event.get_parameter("user"));
    const auto guildID = event.command.guild_id;

	const auto getGuild = dpp::find_guild(guildID);
	const auto tgt_user = getGuild->members.find(userID);

	HarshieDatabase& database = HarshieDatabase::getInstance();
    std::string selectLanguage = database.getSelectLanguage(event.command.usr.id);

    json& languagesJSON = HarshieLanguages::getInstance().getLanguagesJSON();
    auto findDetails = languagesJSON["BAN"][selectLanguage];

	const auto isValidate = cmndValidation(client, event, userID, dpp::p_ban_members, findDetails["ban"]);

	if (!std::get<bool>(isValidate))
	{
		const auto reasonParam = event.get_parameter("reason");
		const auto reason = std::holds_alternative<std::string>(reasonParam)
			? std::get<std::string>(reasonParam)
			: "No reason provided";

		dpp::user user = client.user_get_sync(userID);
		bool isBannedBefore = false;

		try
		{
			client.guild_get_ban_sync(guildID, userID);
			isBannedBefore = true;
		}
		catch (...) {}

		if (!isBannedBefore)
		{
			client.set_audit_reason(reason);
			client.guild_ban_add(guildID, userID);

			if (tgt_user == getGuild->members.end()) {}
		}
	}
}
