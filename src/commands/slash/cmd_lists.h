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

#include <fstream>

#include <dpp/dpp.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include "../../database/database.h"
#include "../../cores/languages.h"
#include "../../cores/select_menus/process_template.h"

// Common commands
void ping(dpp::cluster& client, const dpp::slashcommand_t& event);

// Configure commands
void config_language(dpp::cluster& client, const dpp::slashcommand_t& event);
void config_server(dpp::cluster& client, const dpp::slashcommand_t& event);

// Moderation commands
void ban(dpp::cluster& client, const dpp::slashcommand_t& event);
