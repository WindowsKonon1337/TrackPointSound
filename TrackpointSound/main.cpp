#include <iostream>
#include <fstream>
#include "MouseDevice.hpp"
#include "SoundPlayer.hpp"

using utils::MouseDevice;
using utils::SoundProducer;

int main(const int argc, const char* argv[]) {
    auto player = SoundProducer("../../TrackpointSound/audio/");
    auto device = MouseDevice("/dev/input/event6");
    auto sound = player.getSound();

    sound->play();

    while (true)
    {
        if (device.mouseMoved())
            std::cout <<player.ifEnded() << std::endl;
                //std::cout << "Device: Мышь перемещена" << std::endl;
    }

    return 0;
}
