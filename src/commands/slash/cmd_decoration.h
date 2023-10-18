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

#include <string>

#include <dpp/dpp.h>
#include <nlohmann/json.hpp>

#include "../../cores/languages.h"

inline void sendSucessfulEmbed(std::string selectLanguage, std::string description, const dpp::slashcommand_t& event)
{
    json& languagesJSON = HarshieLanguages::getInstance().getLanguagesJSON();
    auto findDetails = languagesJSON["DECORATION"][selectLanguage];

    auto create_embed = dpp::embed()
        .set_color(0xabf2d3)
        .set_title(findDetails["success"])
        .set_description(description);

    const auto message = dpp::message().add_embed(create_embed);
    event.reply(message);
}

inline void sendErrorEmbed(std::string selectLanguage, std::string description, const dpp::slashcommand_t& event)
{
    json& languagesJSON = HarshieLanguages::getInstance().getLanguagesJSON();
    auto findDetails = languagesJSON["DECORATION"][selectLanguage];

    auto create_embed = dpp::embed()
        .set_color(0x8c7cff)
        .set_title(findDetails["error"])
        .set_description(description);

    const auto message = dpp::message().add_embed(create_embed).set_flags(dpp::m_ephemeral);
    event.reply(message);
}
