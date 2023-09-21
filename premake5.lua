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

include "resources.lua"
include "setup.lua"

workspace "Harshie"
	architecture "x64"
	configurations { "Release" }

project "Harshie"
	kind          "ConsoleApp"
	language      "C++"
	cppdialect    "C++17"
	staticruntime "off"

	outputdir = "%{cfg.buildcfg}"

	targetdir ("%{wks.location}/x64/%{cfg.buildcfg}")
	objdir    ("%{wks.location}/x64/%{cfg.buildcfg}")

	includedirs{ "include", "include/dpp" }
	libdirs    { "lib" }
	links      { "dpp.lib", "libpq.lib" }
	files      { 
		"src/**.cpp", 
		"src/commands/slash/**.h",
            "src/commands/slash/cmd_common/**.cpp",
        "src/cores/**.h",
        "src/cores/**.cpp",
		"src/database/**.h",
        "src/database/**.cpp",
		"resources/*.h",
        "resources/*.rc",
	}

	filter { "system:windows", "toolset:msc" }
		systemversion "latest"

	filter "configurations:Release"
		runtime  "Release"
		optimize "on"
		
