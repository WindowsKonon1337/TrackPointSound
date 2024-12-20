#include "SoundPlayer.hpp"
#include "LoadSampleFromFileFailException.hpp"
#include "EmptyAudioFolderException.hpp"


namespace utils
{
    SoundPlayer::SoundPlayer(const std::string& audioFolderPath) : audioFolderPath(audioFolderPath)
    {
        namespace fs = std::filesystem;
        for (const auto& elem : fs::directory_iterator(audioFolderPath))
        {
            samples.push_back(
                std::string(elem.path())
            );
        }

        if (!samples.size())
        {
            throw EmptyAudioFolderException("directory " + audioFolderPath + " does not contains any files");
        }
        
        randomGenerator = std::make_unique<std::mt19937>(std::random_device{}());
    }

    void SoundPlayer::playRandomSound()
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

    bool SoundPlayer::isPlayingSound() const
    {
        if (currentSound == nullptr)
        {
            return false;
        }
        return currentSound->getStatus() == sf::Sound::Status::Playing;
    }

    const std::string& SoundPlayer::getRandomSample() const
    {
        return samples[(*randomGenerator)() % samples.size()];
    }
}
