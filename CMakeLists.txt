cmake_minimum_required(VERSION 3.25)
project(COP3530project3)

set(CMAKE_CXX_STANDARD 11)

add_executable(COP3530project3
        #FinalProject/main.cpp
        FinalProject/Flights.h
        FinalProject/Flights.cpp
        FinalProject/Sort.h
        FinalProject/test-unit/test.cpp
        FinalProject/FlightData.cpp FinalProject/FlightData.h)
