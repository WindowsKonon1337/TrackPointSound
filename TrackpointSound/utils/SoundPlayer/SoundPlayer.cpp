#include "SoundPlayer.hpp"
#include "LoadSampleFromFileFailException.hpp"

#include <random>

namespace utils
{
    SoundProducer::SoundProducer(const std::string& audioFolderPath) : audioFolderPath(audioFolderPath)
    {
        namespace fs = std::filesystem;
        for (const auto& elem : fs::directory_iterator(audioFolderPath))
            samples.push_back(elem.path());
    }

    std::shared_ptr<sf::Sound> SoundProducer::getSound()
    {
        buffer = std::make_shared<sf::SoundBuffer>();

        auto samplePath = getRandomSample();

        if (!buffer->loadFromFile(samplePath))
            throw LoadSamplefromFileFailException("error");

        currentSound = std::make_shared<sf::Sound>();

        currentSound->setBuffer(*buffer);

        return currentSound;
    }

    bool SoundProducer::ifEnded() const
    {
        if (currentSound->getStatus() != sf::Sound::Status::Playing)
            return true;

        return false;
    }

    std::string SoundProducer::getRandomSample() const
    {
        SamplesVec out;
        std::sample(
            samples.begin(),
            samples.end(),
            std::back_inserter(out),
            1,
            std::mt19937{std::random_device{}()}
        );

        return *out.begin();
    }
}