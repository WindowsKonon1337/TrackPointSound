#include "MouseDevice.hpp"
#include "SoundPlayer.hpp"
#include "DeviceDiscovery.hpp"
#include <cstdlib>

using utils::MouseDevice;
using utils::SoundPlayer;
using utils::DeviceDiscovery;

int main(const int argc, const char* argv[]) {
    SoundPlayer player(std::string(std::getenv("HOME")) + "/.trackpointsound/audio/");
    MouseDevice device(DeviceDiscovery().getTrackpointEventPath());

    while (true)
    {
        if (device.isMouseMoved() && !player.isPlayingSound())
        {
            player.playRandomSound();
        }
    }

    return 0;
}
