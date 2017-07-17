cmake_minimum_required(VERSION 3.1)

project(Flamingo)

set (CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt5Widgets)
find_package(Qt5Sql)

include_directories(".")

file(GLOB_RECURSE Flamingo_SRC
    "*.h"
    "*.cpp"
    "*.hpp"
)

add_executable(${PROJECT_NAME} ${Flamingo_SRC} "res/main.qrc")

target_link_libraries(${PROJECT_NAME} -lpthread)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Sql)

