cmake_minimum_required(VERSION 2.8)

project (pithreading)

#find_package(Boost 1.55 REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})
#include_directories(${CMAKE_SOURCE_DIR})

#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Modules)

include_directories(BEFORE src ${CMAKE_CURRENT_BINARY_DIR})

include(CheckIncludeFile)

add_subdirectory(src)
#add_subdirectory(test)
