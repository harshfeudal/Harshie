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
    const auto ws_ping = fmt::format("`{0:.02f} ms`", event.from->websocket_ping * 1000);
    const auto rest_ping = fmt::format("`{0:.02f} ms`", event.from->creator->rest_ping * 1000);

    const std::string message = fmt::format("WebSocket ping: {}\nBot latency: {}", ws_ping, rest_ping);

    event.reply(
        dpp::message(message).set_flags(dpp::m_ephemeral)
    );
}
