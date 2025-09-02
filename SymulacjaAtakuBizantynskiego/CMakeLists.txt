cmake_minimum_required(VERSION 3.29)
project(bizcpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(bizcpp main.cpp
        SocialImpactModel.h
        SocialImpactModel.cpp
        Graphs.cpp
        Graphs.h
)
