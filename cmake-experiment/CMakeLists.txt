cmake_minimum_required(VERSION 3.20.0)
set(PROJECT_NAME cmake-experiment)
project(${PROJECT_NAME} VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ../bin)
set(WORKING_DIRECTORY ../bin)

include_directories(include)
link_directories(lib)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.cxx" "src/*.c")
file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.hpp")

# Add find_packages here.
find_package(jsoncpp CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ../bin)
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

# Add libraries here.
target_link_libraries(${PROJECT_NAME} PRIVATE
    jsoncpp_lib
    jsoncpp_object
)