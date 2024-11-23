cmake_minimum_required(VERSION 3.14)

project(server LANGUAGES CXX)

find_package(SFML COMPONENTS audio system REQUIRED)

include_directories(
    utils/MouseDevice
    utils/SoundPlayer
    Exceptions/DevOpenFailException
)

add_executable(
    TrackpointSound
    ./main.cpp
    utils/MouseDevice/MouseDevice.cpp
    utils/SoundPlayer/SoundPayer.cpp
)

target_link_libraries(TrackpointSound sfml-audio sfml-system)
