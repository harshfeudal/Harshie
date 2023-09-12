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

#include "harshie.h"

#include "../commands/slash/cmd_register.h"

Harshie::Harshie()
{
    HarshieDotenv dotenv;
    dotenv.load(".env");

    const auto encodedToken = dotenv.get("ENCODED_CLIENT_TOKEN");
    const auto token = HarshieDecoder::Decode(encodedToken);

    client = std::make_unique<dpp::cluster>(token, dpp::i_all_intents);
    client->on_log(dpp::utility::cout_logger());

    HarshieOnReady();
    HarshieOnSlashCmnd();
}

void Harshie::HarshieStart()
{
    client->start(dpp::st_wait);
}

void Harshie::HarshieOnReady()
{
    client->on_ready([this](const dpp::ready_t& event) 
        {
            HarshieActivites(event);
            HarshieRegisterSlashCmnd();
        });
}

void Harshie::HarshieActivites(const dpp::ready_t& event)
{
    client->set_presence(dpp::presence(dpp::ps_dnd, dpp::at_game, "Looking for moderation"));
    fmt::print("[{}]: {} is online!\n", dpp::utility::current_date_time(), client->me.format_username());
}

void Harshie::HarshieRegisterSlashCmnd()
{
    try 
    {
        registerSlashCommand(*client);

        fmt::print(
            "[{}]: Successfully registered application (/) commands!\n", 
            dpp::utility::current_date_time()
        );  
    }
    catch (...) 
    { 
        fmt::print(
            "[{}]: Fail to register application (/) commands!\n", 
            dpp::utility::current_date_time()
        );
    }
}

void Harshie::HarshieOnSlashCmnd()
{
    client->on_slashcommand([this](const dpp::slashcommand_t& event) 
        {
            dpp::command_interaction data = event.command.get_command_interaction();
			auto iterator = commands.find(data.name);

			if (iterator != commands.end())
				iterator->second.function(*client, event);
        });
}
