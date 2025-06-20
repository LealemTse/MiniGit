cmake_minimum_required(VERSION 3.10)
project(MiniGit)

set(CMAKE_CXX_STANDARD 17)

add_executable(MiniGit
        main.cpp
        Repository.cpp
        log.h
        log.cpp
        branch.cpp
        branch.h
        checkout.cpp
        checkout.h
)
