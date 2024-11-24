#include "DeviceDiscovery.hpp"


namespace utils
{
std::string DeviceDiscovery::getTrackpointEventPath(bool useCache) 
{
    if (useCache && !this->trackpointEventPathCache.empty()) 
    {
        return this->trackpointEventPathCache;
    }
    std::vector<Device> devices = this->discoverDevices();
    std::vector<Device> trackpoints;
    std::copy_if(devices.begin(), devices.end(), std::back_inserter(trackpoints), DeviceDiscovery::isTrackpoint);
    if (trackpoints.size() == 0) 
    {
        throw TrackpointNotFoundException("no device name satisfy regex `TPPS/2.*TrackPoint`");
    }
    if (trackpoints.size() > 1) 
    {
        std::cerr << "Found " << trackpoints.size() << " trackpoint devices - " << trackpoints[0].eventPath << " (" << trackpoints[0].name << ") will be used";
    }
    this->trackpointEventPathCache = trackpoints[0].eventPath;
    return trackpoints[0].eventPath;
}


inline bool DeviceDiscovery::isTrackpoint(const Device& device) noexcept 
{
    return device.name.starts_with("TPPS/2") && device.name.ends_with("TrackPoint");
}

std::vector<Device> DeviceDiscovery::discoverDevices()
{
    udev *udev = udev_new();
    if (!udev) 
    {
        throw UdevContextFailException("failed to create udev context");
    }

    udev_enumerate *enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "input");
    udev_enumerate_scan_devices(enumerate);

    std::vector<Device> result;

    udev_list_entry *devices, *entry;
    devices = udev_enumerate_get_list_entry(enumerate);
    udev_list_entry_foreach(entry, devices) 
    {
        const char *syspath = udev_list_entry_get_name(entry);
        udev_device *dev = udev_device_new_from_syspath(udev, syspath);

        auto name = this->getDeviceName(dev);
        auto eventPath = this->getDeviceEventPath(dev);
        if (name && eventPath) 
        {
            result.push_back(Device{
                .name = *name,
                .eventPath = *eventPath,
            });
        }

        // Free the device
        udev_device_unref(dev);
    }

    // Free resources
    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    return result;
}

std::optional<std::string> DeviceDiscovery::getDeviceEventPath(udev_device *device)
{
    const char *devnode = udev_device_get_devnode(device);
    if (!devnode) 
    {
        return std::nullopt;
    }
    std::string result(devnode);
    if (!result.starts_with("/dev/input/event")) 
    {
        return std::nullopt;
    }
    return result;
}

std::optional<std::string> DeviceDiscovery::getDeviceName(udev_device *device) 
{
    udev_device *parent = udev_device_get_parent(device);
    if (!parent) 
    {
        return std::nullopt;
    }
    const char *result = udev_device_get_sysattr_value(parent, "name");
    if (!result) 
    {
        return std::nullopt;
    }
    return std::string(result);
}

}