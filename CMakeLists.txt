cmake_minimum_required(VERSION 3.10)
project(interconnection)

set(CMAKE_CXX_STANDARD 14)

add_executable(interconnection main.cxx Server.cxx Server.hxx Client.cxx Client.hxx)