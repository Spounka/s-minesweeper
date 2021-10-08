cmake_minimum_required(VERSION 3.10)
project(SMinesweeper)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory("extern/SFML-2.5.1")

include_directories("extern/SFML-2.5.1/include")
include_directories("include")

set(PROJECT_SOURCE_FILES "src/main.cpp" "src/button.cpp"
                         "src/resourcesmanager.cpp")

set(PROJECT_HEADER_FILES "include/button.hpp" "include/resourcesmanager.hpp"
                         "include/config.hpp")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} sfml-window sfml-graphics)

set(RESOURCES_DIR "${CMAKE_BINARY_DIR}/resources")
message(${RESOURCES_DIR})

configure_file("${CMAKE_SOURCE_DIR}/config.hpp.in"
               "${CMAKE_SOURCE_DIR}/include/config.hpp")

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/resources/"
          "${RESOURCES_DIR}")
