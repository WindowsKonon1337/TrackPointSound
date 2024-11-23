#include <iostream>
#include <fstream>
#include "MouseDevice.hpp"
#include <SFML/Audio.hpp>

using utils::MouseDevice;

int main(const int argc, const char* argv[]) {
    auto device = MouseDevice("/dev/input/event6");

    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile("sample_water.ogg")) {
        std::cerr << "Не удалось загрузить звук!" << std::endl;
        return -1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);

    sound.play();

    while (true)
    {
            if (device.mouseMoved())
                std::cout << "Device: Мышь перемещена" << std::endl;
    }

    return 0;
}