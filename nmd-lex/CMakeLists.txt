# Copyright (c) UnnamedOrange. Licensed under the MIT License.
# See the LICENSE file in the repository root for full license text.

cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME "nmd-lex")
project(${PROJECT_NAME}
	VERSION 0.0.0
	DESCRIPTION "Lexer for nmd."
	LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)
target_include_directories(${PROJECT_NAME} INTERFACE
	"include")

add_subdirectory("third-party/utils/native")
target_link_libraries(${PROJECT_NAME} INTERFACE utils)
