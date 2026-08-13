cmake_minimum_required(VERSION 3.2)

project (SpikeStack)

add_library(spikestack SHARED)

target_sources(spikestack
    PRIVATE
        src/LifNeuron.cpp
    
    PUBLIC
        FILE_SET myHeaders
        TYPE HEADERS
        BASE_DIRS
            include
        FILES
            include/LifNeuron.hpp
)