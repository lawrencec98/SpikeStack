cmake_minimum_required(VERSION 3.2)

project (SpikeStack)

add_subdirectory("submodules/googletest")

# Build config for spikestack library
add_library(spikestack SHARED)
target_include_directories(spikestack PUBLIC include)
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


# Build info for test_LifNeuron
add_executable(test_LifNeuron test/test_LifNeuron.cpp)
target_link_libraries(test_LifNeuron PRIVATE GTest::gtest_main spikestack)
target_sources(test_LifNeuron
    PRIVATE
        test/test_LifNeuron.cpp
)