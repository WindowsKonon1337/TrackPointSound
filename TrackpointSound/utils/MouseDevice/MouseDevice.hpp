#pragma once

#include <fstream>
#include <string>


namespace utils{
    class MouseDevice 
    {
    public:
        MouseDevice(const std::string& device);

        MouseDevice() = delete;

        bool mouseMoved();
    private:
        std::ifstream miceDevFile;

        char mouseData[3];
    };
}

