cmake_minimum_required(VERSION 3.21)
project(Preliminary_Proyect)

set(CMAKE_CXX_STANDARD 14)

add_executable(Preliminary_Proyect
        main.cpp
        Employee.cpp
        Employee.h
        AnimalHab.cpp
        AnimalHab.h EmployeeList.cpp EmployeeList.h AnimalList.cpp AnimalList.h Zoo.cpp Zoo.h TestEmployeeList.cpp TestCases.h TestAnimalList.cpp TestZoo.cpp TestAnimalsCondition.cpp)
