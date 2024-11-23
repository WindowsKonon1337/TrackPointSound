#pragma once

#include <string>
#include <filesystem>
#include <memory>

#include <SFML/Audio.hpp>

namespace utils
{
    class SoundProducer
    {
    public:
        SoundProducer(const std::string& audioFolderPath);

        std::shared_ptr<sf::Sound> getSound();

        bool ifEnded() const;
    private:
        std::string getRandomSample() const;

        using SamplesVec = std::vector<std::filesystem::path>;

        std::shared_ptr<sf::Sound> currentSound;
        std::shared_ptr<sf::SoundBuffer> buffer;

        SamplesVec samples;

        const std::string audioFolderPath;
    };
}
