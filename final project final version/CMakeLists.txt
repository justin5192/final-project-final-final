cmake_minimum_required(VERSION 3.27)
project(final_project_final_version)

set(CMAKE_CXX_STANDARD 14)

add_executable(final_project_final_version main.cpp
        BranchAndBound.cpp
        BranchAndBound.h
        ChristofidesAlgorithm.cpp
        ChristofidesAlgorithm.h
        City.cpp
        City.h
        GeneticAlgorithm.cpp
        GeneticAlgorithm.h
        SimulatedAnnealing.cpp
        SimulatedAnnealing.h
        TSPAlgorithm.h
        TSPData.cpp
        TSPData.h)
