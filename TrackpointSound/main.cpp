#include "MouseDevice.hpp"
#include "SoundPlayer.hpp"

using utils::MouseDevice;
using utils::SoundPlayer;

int main(const int argc, const char* argv[]) {
    auto player = SoundPlayer("../../TrackpointSound/audio/");
    auto device = MouseDevice("/dev/input/event6");

    player.play();

    while (true)
    {
        if (device.mouseMoved())
        {
            // do some work
        }
    }

    return 0;
}
