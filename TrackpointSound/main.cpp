#include "MouseDevice.hpp"
#include "SoundPlayer.hpp"
#include "DeviceDiscovery.hpp"

using utils::MouseDevice;
using utils::SoundPlayer;
using utils::DeviceDiscovery;

int main(const int argc, const char* argv[]) {
    // SoundPlayer player("../../TrackpointSound/audio/");
    // MouseDevice device(DeviceDiscovery().getTrackpointEventPath());

    // while (true)
    // {
    //     if (device.isMouseMoved() && !player.isPlayingSound())
    //     {
    //         player.playRandomSound();
    //     }
    // }
    auto devices = DeviceDiscovery().discoverDevices();
    for (const auto& device : devices) {
        std::cout << device.eventPath << " (" << device.name << ")\n";
    }

    return 0;
}
