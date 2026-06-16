cmake_minimum_required(VERSION 3.16)
project(ProductStore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Важно! Эти строки должны быть ДО add_executable
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

add_executable(ProductStore
    main.cpp
    mainwindow.cpp
    mainwindow.h
    add.cpp
    add.h
    search.cpp
    search.h
    draw.cpp
    draw.h
    information.cpp
    information.h
)

target_link_libraries(ProductStore PRIVATE
    Qt6::Widgets
    Qt6::Charts
)
