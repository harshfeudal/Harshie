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

    if (!file.is_open())
        throw std::runtime_error("Failed to open .env file");

    std::string line;
    while (std::getline(file, line)) 
    {
        if (isComment(line))
            continue;

        expandVariables(line);
        parseLine(line);
    }

    file.close();
}

bool HarshieDotenv::has(const std::string& key) const 
{
    return variables_.find(key) != variables_.end();
}

std::string HarshieDotenv::get(const std::string& key) const 
{
    if (!has(key))
        throw std::runtime_error("Undefined key: " + key);

    return variables_.at(key);
}

bool HarshieDotenv::isComment(const std::string& line) 
{
    return line.find("#") == 0;
}

void HarshieDotenv::expandVariables(std::string& line) 
{
    std::size_t pos = 0;

    while ((pos = line.find('$', pos)) != std::string::npos) 
    {
        if (pos + 1 < line.length()) 
        {
            if (line[pos + 1] == '\\') 
            {
                line.erase(pos, 1);
                ++pos;
            } 
            else if (line[pos + 1] == '{') 
            {
                std::size_t endPos = line.find('}', pos + 2);

                if (endPos != std::string::npos) 
                {
                    std::string varName = line.substr(pos + 2, endPos - pos - 2);
                    std::string varValue = (has(varName)) ? get(varName) : "";

                    line.replace(pos, endPos - pos + 1, varValue);
                    pos += varValue.length();
                } 
                else
                    ++pos;
            } 
            else 
            {
                std::string varName = line.substr(pos + 1);
                std::string varValue = (has(varName)) ? get(varName) : "";

                line.replace(pos, varName.length() + 1, varValue);
                pos += varValue.length();
            }
        } 
        else
            break;
    }
}

void HarshieDotenv::parseLine(const std::string& line) 
{
    std::istringstream iss(line);
    std::string key, value;

    if (std::getline(iss >> std::ws, key, '=') && std::getline(iss >> std::ws, value))
        variables_[key] = value;
}