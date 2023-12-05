cmake_minimum_required(VERSION 3.16)

project(mervbot-plugin-template VERSION 0.0.1 DESCRIPTION "A MERVBot plugin template")

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(dep/mervbot)

add_library(${PROJECT_NAME} SHARED
	src/command.cpp
	src/spawn.cpp
)

if (UNIX)
	target_compile_definitions(${PROJECT_NAME} PRIVATE __stdcall=)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE dep/mervbot/src)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
#set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER source/convert.h)

