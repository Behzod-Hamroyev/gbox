cmake_minimum_required(VERSION 3.30)
project(gbox)

set(CMAKE_CXX_STANDARD 20)

add_executable(gbox
        main.cpp
        UniversityMember.cpp
        Administration.cpp
        Faculty.cpp
        Student.cpp
        Registration.cpp
        Manager.cpp
        Database.cpp
)
