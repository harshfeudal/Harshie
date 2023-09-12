--
-- Copyright (C) 2023 harshfeudal
-- 
-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
-- 
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
-- 
-- You should have received a copy of the GNU General Public License
-- along with this program.  If not, see https://www.gnu.org/licenses/.
--

local HARSHIE_VERSION_MAJOR = 1
local HARSHIE_VERSION_MINOR = 0
local HARSHIE_VERSION_PATCH = 0
local HARSHIE_VERSION_BUILD = 0
local HARSHIE_VERSION = HARSHIE_VERSION_MAJOR .. "." .. HARSHIE_VERSION_MINOR .. "." .. HARSHIE_VERSION_PATCH .. "." .. HARSHIE_VERSION_BUILD

local inputFilePath = "resources/harshie.rc.in"
local outputFilePath = "resources/harshie.rc"

local inputFile = io.open(inputFilePath, "r")
if inputFile then
    local fileContents = inputFile:read("*a")
    inputFile:close()

    fileContents = string.gsub(fileContents, "@HARSHIE_VERSION_MAJOR@", tostring(HARSHIE_VERSION_MAJOR))
    fileContents = string.gsub(fileContents, "@HARSHIE_VERSION_MINOR@", tostring(HARSHIE_VERSION_MINOR))
    fileContents = string.gsub(fileContents, "@HARSHIE_VERSION_PATCH@", tostring(HARSHIE_VERSION_PATCH))
    fileContents = string.gsub(fileContents, "@HARSHIE_VERSION_BUILD@", tostring(HARSHIE_VERSION_BUILD))
    fileContents = string.gsub(fileContents, "@HARSHIE_VERSION@", HARSHIE_VERSION)

    local outputFile = io.open(outputFilePath, "w")
    if outputFile then
        outputFile:write(fileContents)
        outputFile:close()
        print("Resource file generated successfully.")
    else
        print("Error: Failed to open the output file for writing.")
    end
else
    print("Error: Failed to open the input file.")
end