#include <string>
#include <vector>
#include <algorithm>
#include <optional>
#include <iostream>

#include <libudev.h>

#include "UdevContextFailException.hpp"
#include "TrackpointNotFoundException.hpp"


namespace utils {
struct Device {
    const std::string name;
    const std::string eventPath;
};

class DeviceDiscovery {
public:
    std::string getTrackpointEventPath(bool useCache=true);

    std::vector<Device> discoverDevices();
private:
    std::string trackpointEventPathCache;

    static inline bool isTrackpoint(const Device& device) noexcept;

    std::optional<std::string> getDeviceEventPath(udev_device *device);

    std::optional<std::string> getDeviceName(udev_device *device);
};
}