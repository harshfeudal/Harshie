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

#include <dpp/dpp.h>
#include <spdlog/spdlog.h>

inline std::tuple<bool, std::string> cmndValidation(dpp::cluster& client, const dpp::slashcommand_t& event, dpp::snowflake userID, dpp::permission permission, std::string cmndName)
{
    std::string description;
    bool isError = false;

    const auto guildID = event.command.guild_id;
    const auto getGuildUser = dpp::find_guild_member(guildID, userID);

    const auto guild = dpp::find_guild(guildID);
    dpp::user user = client.user_get_sync(userID);

    const auto isAdminUser = guild->base_permissions(getGuildUser).has(dpp::p_administrator);
    const auto isAdminIssuer = guild->base_permissions(event.command.member).has(dpp::p_administrator);
    const auto isAdminClient = event.command.app_permissions.has(dpp::p_administrator);

    HarshieDatabase& database = HarshieDatabase::getInstance();
    std::string selectLanguage = database.getSelectLanguage(event.command.usr.id, "language_config", "language");

    json& languagesJSON = HarshieLanguages::getInstance().getLanguagesJSON();
    auto findDetails = languagesJSON["VALIDATION"][selectLanguage];

    if (!guild->base_permissions(event.command.member).has(permission))
    {
        description = fmt::format(findDetails["self-permission"], cmndName);
        isError = true;
    }
    else
    {
        if (!event.command.app_permissions.has(permission))
        {
            description = fmt::format(findDetails["client-permission"], cmndName);
            isError = true;
        }

        if (userID == guild->owner_id)
        {
            description = fmt::format(findDetails["owner-restriction"], cmndName);
            isError = true;
        }

        if (userID == event.command.usr.id)
        {
            description = findDetails["action-failed"];
            isError = true;
        }

        if (userID == client.me.id)
        {
            description = findDetails["client-immuned"];
            isError = true;
        }

        if (isAdminUser)
        {
            if (!isAdminClient)
            {
                description = fmt::format(findDetails["client-no-admin"], cmndName);
                isError = true;
            }

            if (!isAdminIssuer)
            {
                description = fmt::format(findDetails["user-no-admin"], cmndName);
                isError = true;
            }
        }

        const auto userRoles = getGuildUser.roles;
        const auto issuerRoles = dpp::find_guild_member(guildID, event.command.usr.id).roles;

        if (!userRoles.empty() && !issuerRoles.empty() && !isError)
        {
            const auto userPos = dpp::find_role(userRoles.at(0))->position;
            const auto issuerPos = dpp::find_role(issuerRoles.at(0))->position;

            if (issuerPos < userPos)
            {
                description = fmt::format(findDetails["cannot-ban"], cmndName, user.username);
                isError = true;
            }
        }
    }

    return { isError, description };
}
