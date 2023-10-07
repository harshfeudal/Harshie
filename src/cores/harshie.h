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

#pragma warning(push)

#pragma warning(disable: 4251)
#pragma warning(disable: 6385)
#pragma warning(disable: 6285)
#pragma warning(disable: 4700)

#include <dpp/dpp.h>
#include <spdlog/spdlog.h>

#pragma warning(pop)

#include "dotenv.h"
#include "decoder.h"
#include "languages.h"
#include "../database/database.h"
#include "select_menus/process_template.h"

class Harshie 
{
public:
    Harshie();

    void HarshieStart();

private:
    HarshieDotenv dotenv;

    std::unique_ptr<dpp::cluster> client;
    std::string selectLanguage;
    std::string selectMenuValue;

    void HarshieOnReady();
    void HarshieOnSlashCmnd();
    void HarshieOnDatabaseConnect();
    void HarshieOnDatabaseCreate();
    void HarshieOnSelectClicked();

    void HarshieActivites(const dpp::ready_t& event);
    void HarshieRegisterSlashCmnd();

    void HarshieServerConfig(const dpp::select_click_t& event);

    void HarshieLanguagesValue(const dpp::select_click_t& event);
    void HarshieLanguageSelection(const dpp::select_click_t& event);
};
