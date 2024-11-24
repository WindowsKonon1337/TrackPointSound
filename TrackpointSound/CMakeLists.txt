cmake_minimum_required(VERSION 3.14)

project(TrackpointSound LANGUAGES CXX)

find_package(PkgConfig REQUIRED)
find_package(SFML COMPONENTS audio system REQUIRED)
pkg_check_modules(UDEV REQUIRED libudev)

include_directories(
    utils/MouseDevice
    utils/SoundPlayer
    utils/DeviceDiscovery
    Exceptions/DevOpenFailException
    Exceptions/LoadSampleFromFileFailException
    Exceptions/TrackpointNotFoundException
    Exceptions/UdevContextFailException
)

add_executable(
    TrackpointSound
    ./main.cpp
    utils/MouseDevice/MouseDevice.cpp
    utils/SoundPlayer/SoundPlayer.cpp
    utils/DeviceDiscovery/DeviceDiscovery.cpp
)

target_link_libraries(TrackpointSound sfml-audio sfml-system udev)
