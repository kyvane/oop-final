#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager &_formatManager)
    : formatManager(_formatManager)
{
    reverbParameters.wetLevel = 0.33f;
    reverbParameters.dryLevel = 0.4f;
    reverbParameters.damping = 0.5f;
    reverbParameters.roomSize = 0.5f;
    reverbParameters.width = 1.0f;
    reverbParameters.freezeMode = 0.0f;
}

DJAudioPlayer::~DJAudioPlayer()
{
}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    reverbSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    bass.setCoefficients(juce::IIRCoefficients::makeLowShelf(sampleRate, 200.0, 1.0, 1));
    bass.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mid.setCoefficients(juce::IIRCoefficients::makePeakFilter(sampleRate, 4000, 0.5, 1));
    mid.prepareToPlay(samplesPerBlockExpected, sampleRate);

    high.setCoefficients(juce::IIRCoefficients::makeHighShelf(sampleRate, 200.0, 1.0, 1));
    high.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    reverbSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
    reverbSource.releaseResources();

    bass.releaseResources();
    mid.releaseResources();
    high.releaseResources();
}

void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    auto *reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader,
                                                                                                   true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
    else
    {
        DBG("failed to load file");
    }
}
void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else
    {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio)
{
    if (ratio < 0 || ratio > 100.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 1" << std::endl;
    }
    else
    {
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else
    {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::setHigh(double highLevel)
{
    if (highLevel < 2 && highLevel > 0)
        bass.setCoefficients(juce::IIRCoefficients::makeHighPass(200.0, static_cast<float>(highLevel), rate));
}

void DJAudioPlayer::setMid(double midLevel)
{
    if (midLevel < 2 && midLevel > 0)
        bass.setCoefficients(juce::IIRCoefficients::makePeakFilter(rate, 4000.0, 0.5, static_cast<float>(midLevel)));
}

void DJAudioPlayer::setLow(double lowLevel)
{
    if (lowLevel < 2 && lowLevel > 0)
        bass.setCoefficients(juce::IIRCoefficients::makeLowShelf(rate, 200.0, 1.0, static_cast<float>(lowLevel)));
}

void DJAudioPlayer::setWet(float wet)
{
    if (wet < 0 || wet > 1.0)
    {
        std::cout << "DJAudioPlayer::setWet wet level should be between 0 and 1" << std::endl;
    }
    else
    {
        reverbParameters.wetLevel = wet;
        reverbSource.setParameters(reverbParameters);
    }
}

void DJAudioPlayer::setDamping(float damping)
{
    if (damping < 0 || damping > 1.0)
    {
        std::cout << "DJAudioPlayer::setDamping damping level should be between 0 and 1" << std::endl;
    }
    else
    {
        reverbParameters.damping = damping;
        reverbSource.setParameters(reverbParameters);
    }
}

void DJAudioPlayer::setRoomSize(float roomSize)
{
    if (roomSize < 0 || roomSize > 1.0)
    {
        std::cout << "DJAudioPlayer::setRoomSize size should be between 0 and 1" << std::endl;
    }
    else
    {
        reverbParameters.roomSize = roomSize;
        reverbSource.setParameters(reverbParameters);
    }
}

void DJAudioPlayer::setDry(float dry)
{
    if (dry < 0 || dry > 1.0)
    {
        std::cout << "DJAudioPlayer::setDry dry level should be between 0 and 1" << std::endl;
    }
    else
    {
        reverbParameters.dryLevel = dry;
        reverbSource.setParameters(reverbParameters);
    }
}

void DJAudioPlayer::setFreeze(float freeze)
{
    reverbParameters.freezeMode = freeze;
    reverbSource.setParameters(reverbParameters);
}

void DJAudioPlayer::setWidth(float width)
{
    if (width < 0 || width > 1.0)
    {
        std::cout << "DJAudioPlayer::setWidth width should be between 0 and 1" << std::endl;
    }
    else
    {
        reverbParameters.width = width;
        reverbSource.setParameters(reverbParameters);
    }
}

void DJAudioPlayer::start()
{
    transportSource.start();
}

void DJAudioPlayer::stop()
{
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}
