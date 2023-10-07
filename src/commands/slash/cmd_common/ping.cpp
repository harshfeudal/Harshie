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

void ping(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    const auto wsPing = fmt::format("`{0:.02f} ms`", event.from->websocket_ping * 1000);
    const auto restPing = fmt::format("`{0:.02f} ms`", event.from->creator->rest_ping * 1000);

    HarshieDatabase& database = HarshieDatabase::getInstance();
    std::string selectLanguage = database.getSelectLanguage(event.command.usr.id, "language_config", "language");

    json& languagesJSON = HarshieLanguages::getInstance().getLanguagesJSON();
    auto findDetails = languagesJSON["PING"][selectLanguage];

    auto create_embed = dpp::embed()
        .set_title(findDetails["title"])
        .set_color(0xabf2d3)
        .add_field(findDetails["websocket"], wsPing, true)
        .add_field(findDetails["roundtrip"], restPing, true)
        .set_footer(
            dpp::embed_footer()
                .set_text(client.me.format_username())
                .set_icon(client.me.get_avatar_url())
        )
        .set_timestamp(time(0));

    event.reply(
        dpp::message().add_embed(create_embed).set_flags(dpp::m_ephemeral)
    );
}
