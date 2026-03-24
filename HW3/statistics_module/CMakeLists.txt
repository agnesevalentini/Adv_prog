cmake_minimum_required(VERSION 3.14) # Cmake version required 
project(Statistics_module)  # Project name

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # enforce the standard 

# Add Boost and pybind11 paths
set(PYBIND11_FINDPYTHON ON) # enables pybind to search for python configurations automatically
set(BOOST_ROOT "/usr/local/include/boost")
set(BOOST_INCLUDEDIR "/usr/local/include/boost/include") 
set(BOOST_LIBRARYDIR "/usr/local/include/boost/libs") 
set(Python_ROOT_DIR "/usr")
set(Python_INCLUDE_DIR "/usr/include/python3.12")


find_package(Python 3.12 EXACT REQUIRED COMPONENTS Interpreter Development) # find python version 3.12
find_package(Boost)
find_package(pybind11 REQUIRED) # find pybind11

# Include directories for Boost
include_directories(${Boost_INCLUDE_DIRS})

# specification of the source files
set(SRCS "statistics_module.cpp;stat_bindings.cpp")


# Create the library
add_library(StatisticsLib ${SRCS})
pybind11_add_module(statistics_module ${SRCS})

# Link Boost to the library
target_link_libraries(StatisticsLib PRIVATE ${Boost_LIBRARIES})

# Python bindings
target_link_libraries(statistics_module PRIVATE StatisticsLib ${Boost_LIBRARIES})

# Add include directories
target_include_directories(StatisticsLib PUBLIC ${CMAKE_SOURCE_DIR})

target_include_directories(StatisticsLib PRIVATE ${Python_INCLUDE_DIRS})
target_link_libraries(StatisticsLib PRIVATE ${Python_LIBRARIES})

target_include_directories(statistics_module PRIVATE ${Python_INCLUDE_DIRS})
target_link_libraries(statistics_module PRIVATE ${Python_LIBRARIES})



# compilation flags
target_compile_definitions(statistics_module PRIVATE)

# Imposta le flag di compilazione C++
target_compile_options(statistics_module PRIVATE -Wall -Wextra -Wpedantic)


#eventually install the module
install(TARGETS statistics_module DESTINATION .)