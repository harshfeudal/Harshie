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

#include "dotenv.h"

void HarshieDotenv::load(const std::string& filename) 
{
    std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

    std::string line;
    while (std::getline(file, line)) {
    	if (line.empty() || line[0] == '#')
    		continue;

		size_t pos = line.find('=');
		if (pos == std::string::npos)
			continue;

		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1);

		if (!value.empty() && value[0] == '"' && value[value.size() - 1] == '"')
			value = value.substr(1, value.size() - 2);

		m_data[key] = value;
	}
}

std::string HarshieDotenv::get(const std::string& key) const 
{
    auto it = m_data.find(key);
		if (it != m_data.end()) {
			return it->second;
		}
		return "";
}
