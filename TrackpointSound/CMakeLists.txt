cmake_minimum_required(VERSION 3.14)

project(server LANGUAGES CXX)

find_package(SFML COMPONENTS audio system REQUIRED)

include_directories(
    utils/MouseDevice
    utils/SoundProducer
    Exceptions/DevOpenFailException
    Exceptions/LoadSampleFromFileFailException
)

add_executable(
    TrackpointSound
    ./main.cpp
    utils/MouseDevice/MouseDevice.cpp
    utils/SoundProducer/SoundProducer.cpp
)

target_link_libraries(TrackpointSound sfml-audio sfml-system)
