cmake_minimum_required(VERSION 3.25)
project(COP3530project3)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES FinalProject/constants.h
        FinalProject/Flights.cpp
        FinalProject/Flights.h
        FinalProject/main.cpp
        FinalProject/TextureManager.cpp
        FinalProject/TextureManager.h
        )

include_directories(/usr/local/include)

add_executable(COP3530project3
        FinalProject/constants.h
        FinalProject/Flights.cpp
        FinalProject/Flights.h
        FinalProject/main.cpp
        FinalProject/TextureManager.cpp
        FinalProject/TextureManager.h)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(COP3530project3 sfml-system sfml-window sfml-graphics)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(COP3530project3 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

