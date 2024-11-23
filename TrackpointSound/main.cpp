#include "MouseDevice.hpp"
#include "SoundProducer.hpp"

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
        {
            // do some work
        }
    }

    return 0;
}
