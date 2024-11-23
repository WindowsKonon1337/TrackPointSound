#include "SoundPlayer.hpp"
#include "LoadSampleFromFileFailException.hpp"


namespace utils
{
    SoundPlayer::SoundPlayer(const std::string& audioFolderPath) : audioFolderPath(audioFolderPath)
    {
        namespace fs = std::filesystem;
        for (const auto& elem : fs::directory_iterator(audioFolderPath))
        {
            samples.push_back(elem.path());
        }
        
        randomGenerator = std::make_unique<std::mt19937>(std::random_device{}());
    }

    void SoundPlayer::play()
    {
        buffer = std::make_shared<sf::SoundBuffer>();

        auto samplePath = getRandomSample();

        if (!buffer->loadFromFile(samplePath))
        {
            throw LoadSamplefromFileFailException("error");
        }

        currentSound = std::make_shared<sf::Sound>();

        currentSound->setBuffer(*buffer);

        currentSound->play();
    }

    bool SoundPlayer::isEnded() const
    {
        return currentSound->getStatus() != sf::Sound::Status::Playing;
    }

    std::string SoundPlayer::getRandomSample() const
    {
        return samples[(*randomGenerator)() % samples.size()];
    }
}