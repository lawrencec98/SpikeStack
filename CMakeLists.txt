cmake_minimum_required(VERSION 3.2)

project (SpikeStack)

add_subdirectory("submodules/googletest")

# Build config for spikestack library
add_library(spikestack SHARED)
target_include_directories(spikestack PUBLIC include)
target_sources(spikestack
    PRIVATE
        src/EventDispatcher.cpp
        src/LifNeuron.cpp
        src/Synapse.cpp
    
    PUBLIC
        FILE_SET myHeaders
        TYPE HEADERS
        BASE_DIRS
            include
        FILES
            include/Event.hpp
            include/EventDispatcher.hpp
            include/EventQueue.hpp
            include/EventType.hpp
            include/INeuron.hpp
            include/InputNeuron.hpp
            include/LifNeuron.hpp
            include/Spike.hpp
            include/Synapse.hpp
            include/Types.hpp
)


# Build info for test_LifNeuron
add_executable(test_LifNeuron test/test_LifNeuron.cpp)
target_link_libraries(test_LifNeuron PRIVATE GTest::gtest_main GTest::gmock_main spikestack)
target_sources(test_LifNeuron
    PRIVATE
        test/test_LifNeuron.cpp
)


add_executable(main samples/main.cpp)
target_link_libraries(main PRIVATE spikestack)
target_sources(main
    PRIVATE
        samples/main.cpp
)