cmake_minimum_required(VERSION 3.27)
project(comerciolocal)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_executable(comerciolocal main.cpp
        carrinhos.cpp
        carrinhos.h
        logs.cpp
        logs.h
        menus.cpp
        menus.h
        produtos.cpp
        produtos.h
)
