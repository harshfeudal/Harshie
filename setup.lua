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

local sourceDir = "bin"
local destinationDir = "x64/Release"

function copyFiles(source, destination)
    for _, filename in ipairs(os.matchfiles(source .. "/*")) do
        local destFile = path.join(destination, path.getname(filename))
        os.mkdir(path.getdirectory(destFile))
        os.copyfile(filename, destFile)
    end
end

-- Copy the .env
local envFile = ".env"
if os.isfile(envFile) then
    local destEnvFile = path.join(destinationDir, envFile)
    os.copyfile(envFile, destEnvFile)
    print(".env file copied to x64/Release.")
else
    print(".env file not found in the root directory.")
end

-- Copy the languages.json
local langFile = "languages.json"
if os.isfile(langFile) then
    local destLangFile = path.join(destinationDir, langFile)
    os.copyfile(langFile, destLangFile)
    print("languages.json file copied to x64/Release.")
else
    print("languages.json file not found in the root directory.")
end

if not os.isdir(destinationDir) then
    os.mkdir(destinationDir)
end

copyFiles(sourceDir, destinationDir)

print("Copying DLLs to x64/Release completed.")
