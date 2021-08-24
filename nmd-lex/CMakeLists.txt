# Copyright (c) UnnamedOrange. Licensed under the MIT License.
# See the LICENSE file in the repository root for full license text.

cmake_minimum_required(VERSION 3.16)
project("nmd-lex"
	VERSION 0.0.0
	DESCRIPTION "Lexer for nmd."
	LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
set(WORKING_DIRECTORY "../bin")

file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*.cxx" "src/*.cc")
file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.hpp")
add_executable(main "${SRC_FILES}" "${HEADER_FILES}")

target_include_directories(main PUBLIC "include")

target_compile_features(main PUBLIC cxx_std_20)
if(MSVC)
  target_compile_options(main PRIVATE /W4)
else()
  target_compile_options(main PRIVATE -Wall -Wextra -pedantic)
endif()
set_target_properties(main PROPERTIES
    CXX_EXTENSIONS OFF
    VS_DEBUGGER_WORKING_DIRECTORY "../bin/${config}")

add_subdirectory("third-party/utils/native")
target_link_libraries(main PUBLIC utils)
