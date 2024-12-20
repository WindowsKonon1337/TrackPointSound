#pragma once

#include <string>
#include <filesystem>
#include <memory>
#include <random>

#include <SFML/Audio.hpp>

namespace utils
{
    class SoundPlayer
    {
    public:
        SoundPlayer(const std::string& audioFolderPath);

        void playRandomSound();

        bool isPlayingSound() const;
    private:
        const std::string& getRandomSample() const;

        using SamplesVec = std::vector<std::string>;

        std::shared_ptr<sf::Sound> currentSound;
        std::shared_ptr<sf::SoundBuffer> buffer;

        SamplesVec samples;

        std::unique_ptr<std::mt19937> randomGenerator;
        
        const std::string audioFolderPath;
    };
}
