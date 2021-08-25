# Copyright (c) UnnamedOrange. Licensed under the MIT License.
# See the LICENSE file in the repository root for full license text.

cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME "nmd-grammar")
project(${PROJECT_NAME}
	VERSION 0.0.0
	DESCRIPTION "Grammar analyser for nmd."
	LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
set(WORKING_DIRECTORY "../bin")

file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*.cxx" "src/*.cc")
file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.hpp")
add_executable(${PROJECT_NAME} "${SRC_FILES}" "${HEADER_FILES}")

target_include_directories(${PROJECT_NAME} PUBLIC "include")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    VS_DEBUGGER_WORKING_DIRECTORY "../bin/${config}")

add_subdirectory("../nmd-lex" "third-party/nmd-lex")
target_link_libraries(${PROJECT_NAME} PUBLIC "nmd-lex")
