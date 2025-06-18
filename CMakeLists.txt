cmake_minimum_required(VERSION 3.31)
project(MiniGit)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenSSL REQUIRED)
target_link_libraries(MiniGit OpenSSL::Crypto)

add_executable(MiniGit
        Repository.cpp
        Repository.h
        main.cpp
        Blob.cpp
        Blob.h)
target_link_libraries(MiniGit OpenSSL::Crypto)