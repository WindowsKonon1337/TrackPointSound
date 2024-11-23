#pragma once

#include <fstream>
#include <string>


namespace utils
{
    class MouseDevice 
    {
    public:
        MouseDevice(const std::string& device);

        MouseDevice() = delete;

        bool isMouseMoved();
    private:
        std::ifstream miceDevFile;

        char mouseData[3];
    };
}

