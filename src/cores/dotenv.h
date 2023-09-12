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

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdexcept>

class HarshieDotenv 
{
public:
    void load(const std::string& filename);
    bool has(const std::string& key) const;
    std::string get(const std::string& key) const;

private:
    std::unordered_map<std::string, std::string> variables_;

    bool isComment(const std::string& line);
    void expandVariables(std::string& line);
    void parseLine(const std::string& line);
};