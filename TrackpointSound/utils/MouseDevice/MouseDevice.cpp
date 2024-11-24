#include "MouseDevice.hpp"
#include "DevOpenFailException.hpp"

namespace utils
{
    MouseDevice::MouseDevice(const std::string& device)
    {
        this->miceDevFile = std::ifstream(device, std::ios::in | std::ios::binary);

        if (!miceDevFile.is_open())
        {
            throw DevOpenFailException("Failed to open " + device + " device\nMake sure to provide sufficient rights: sudo chmod a+r " + device);
        }
    }

    bool MouseDevice::isMouseMoved()
    {
        miceDevFile.read(mouseData, sizeof(mouseData));
        if (miceDevFile.gcount() != sizeof(mouseData))
        {
            return false;
        }
        int x = static_cast<int8_t>(mouseData[1]);
        int y = static_cast<int8_t>(mouseData[2]);
        return x != 0 || y != 0;
    }
}
