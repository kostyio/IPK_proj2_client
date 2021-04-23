cmake_minimum_required(VERSION 3.19)
project(client)

set(CMAKE_CXX_STANDARD 17)

add_executable(client ipk_simpleftp_client.cpp ipk_simpleftp_client.h client_core.cpp client_core.h client_command_processor.cpp client_command_processor.h)