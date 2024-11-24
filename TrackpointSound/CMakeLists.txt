cmake_minimum_required(VERSION 3.14)

project(TrackpointSound LANGUAGES CXX)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: Ensure no fallback to older standards
set(CMAKE_CXX_EXTENSIONS OFF)

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
