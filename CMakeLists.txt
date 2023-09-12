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

aux_source_directory(src/commands COMMANDS)
aux_source_directory(src/commands/slash/cmd_common COMMON_CMDS)
aux_source_directory(src/commands/slash/cmd_moderation MODERATION_CMDS)

add_executable(${PROJECT_NAME} 
    ${MAINSRC} 
    ${COMMANDS} 
        ${COMMON_CMDS} 
        ${MODERATION_CMDS} 
    ${CORES} 
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set(INCLUDE_INTERNAL "include")
set(INCLUDE_EXTERNAL "/usr/include")

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${INCLUDE_INTERNAL} 
    ${INCLUDE_EXTERNAL}
)

target_link_libraries(${PROJECT_NAME} PRIVATE "/lib/libdpp.so")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/.env $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
