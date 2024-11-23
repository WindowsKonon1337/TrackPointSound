#include "MouseDevice.hpp"
#include "SoundPlayer.hpp"

using utils::MouseDevice;
using utils::SoundPlayer;

int main(const int argc, const char* argv[]) {
    auto player = SoundPlayer("../../TrackpointSound/audio/");
    auto device = MouseDevice("/dev/input/event6");

    while (true)
    {
        if (device.mouseMoved() && player.isEnded())
        {
            player.play();
        }
    }

    return 0;
}
