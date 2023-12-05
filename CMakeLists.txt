cmake_minimum_required(VERSION 3.16)

project(mervbot-plugin-template VERSION 0.0.1 DESCRIPTION "A MERVBot plugin template")

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(dep/mervbot)

add_library(${PROJECT_NAME} SHARED
	src/command.cpp
	src/spawn.cpp
	dep/mervbot/src/dllcore.cpp
	dep/mervbot/src/datatypes.cpp
	dep/mervbot/src/algorithms.cpp
#	dep/mervbot/src/player.cpp
	dep/mervbot/src/commtypes.cpp
)

if (UNIX)
	target_compile_definitions(${PROJECT_NAME} PRIVATE __stdcall=)
else()
	target_compile_definitions(${PROJECT_NAME} PRIVATE STRING_CAST_CHAR)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE dep/mervbot/src)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
#set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER source/convert.h)

add_custom_target(
	${PROJECT_NAME}-config ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/dep/mervbot/MERVBot.INI ${CMAKE_CURRENT_SOURCE_DIR}/dep/mervbot/cfg/Commands.txt ${CMAKE_CURRENT_SOURCE_DIR}/dep/mervbot/cfg/Operators.txt ${CMAKE_CURRENT_SOURCE_DIR}/cfg/Spawns.txt $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMENT "Copying configuration files to plugin output directory..."
)

add_custom_target(
	${PROJECT_NAME}-symlink ALL
	# see https://github.com/ament/ament_cmake/issues/350
	#COMMAND ${CMAKE_COMMAND} -E create_symlink $<TARGET_FILE:MERVBot> $<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:MERVBot>
	COMMAND ${CMAKE_COMMAND} -E create_hardlink $<TARGET_FILE:MERVBot> $<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:MERVBot>
	COMMENT "Symlinking MERVBot into plugin output directory..."
)