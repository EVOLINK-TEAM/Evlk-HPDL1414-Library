# Evolink HPDL1414 Library
# https://github.com/EVOLINK-TEAM/Evlk-74HC595-Library
# BSD License

cmake_minimum_required(VERSION 3.5)
project(evlk_hpdl1414)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src srcs)
set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(requires arduino evlk_nopins)

idf_component_register(SRCS ${srcs}
    INCLUDE_DIRS ${include_dirs}
    REQUIRES ${requires})