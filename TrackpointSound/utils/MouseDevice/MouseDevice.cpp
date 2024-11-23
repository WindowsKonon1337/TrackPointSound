#include "MouseDevice.hpp"
#include "DevOpenFailException.hpp"

namespace utils
{
    MouseDevice::MouseDevice(const std::string& device)
    {
        this->miceDevFile = std::ifstream(device, std::ios::in | std::ios::binary);

        if (!miceDevFile.is_open())
        {
            throw DevOpenFailException("Failed to open device");
        }
    }

    bool MouseDevice::mouseMoved()
    {
        miceDevFile.read(mouseData, sizeof(mouseData));
        if (miceDevFile.gcount() == sizeof(mouseData))
        {
            int x = static_cast<int8_t>(mouseData[1]);
            int y = static_cast<int8_t>(mouseData[2]);
            if (x != 0 || y != 0)
            {
                return true;
            }
        }

        return false;
    }
}
