#
# Copyright (C) 2023 harshfeudal
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see https://www.gnu.org/licenses/.
#

cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME "Harshie")

set(HARSHIE_VERSION_MAJOR 1)
set(HARSHIE_VERSION_MINOR 0)
set(HARSHIE_VERSION_PATCH 0)
set(HARSHIE_VERSION_BUILD 0)
set(HARSHIE_VERSION ${HARSHIE_VERSION_MAJOR}.${HARSHIE_VERSION_MINOR}.${HARSHIE_VERSION_PATCH}.${HARSHIE_VERSION_BUILD})

project(
    ${PROJECT_NAME} 
        VERSION ${HARSHIE_VERSION} 
        LANGUAGES CXX 
    DESCRIPTION "A simple Discord moderation bot written in C++"
)

aux_source_directory(src MAINSRC)
aux_source_directory(src/cores CORES)
aux_source_directory(src/database DATABASE)

aux_source_directory(src/commands COMMANDS)
aux_source_directory(src/commands/slash/cmd_common COMMON_CMDS)
aux_source_directory(src/commands/slash/cmd_moderation MODERATION_CMDS)

add_executable(${PROJECT_NAME} 
    ${MAINSRC} 
    ${COMMANDS} 
        ${COMMON_CMDS} 
        ${MODERATION_CMDS} 
    ${CORES} 
    ${DATABASE} 
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set(INCLUDE_FOLDER "include")
set(DPP_FOLDER "include/dpp")

set(LIBRARY_FOLDER "lib")

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${INCLUDE_FOLDER} 
    ${DPP_FOLDER} 
)

if(WIN32)
    target_include_directories(${PROJECT_NAME} PRIVATE ${LIBRARY_FOLDER})

    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/dpp.lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/libpq.lib)

    target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_BINARY_DIR}/harshie.rc")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/bin $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    configure_file(
        ${CMAKE_SOURCE_DIR}/resources/harshie.rc.in 
        ${CMAKE_BINARY_DIR}/harshie.rc 
        @ONLY
    )

else()
    target_link_libraries(${PROJECT_NAME} PRIVATE "/lib/libdpp.so")

    find_package(PostgreSQL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL)

endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/.env $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
