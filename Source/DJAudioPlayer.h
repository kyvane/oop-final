#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public juce::AudioSource
{
public:
    DJAudioPlayer(juce::AudioFormatManager &_formatManager);
    ~DJAudioPlayer();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
    void releaseResources() override;

    void loadURL(juce::URL audioURL);

    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);

    void setWet(float wet);
    void setDamping(float damping);
    void setRoomSize(float roomSize);
    void setDry(float dry);
    void setFreeze(float freeze);
    void setWidth(float width);

    void setHigh(double highLevel);
    void setMid(double midLevel);
    void setLow(double lowLevel);

    void start();
    void stop();

    double getPositionRelative();

private:
    juce::AudioFormatManager &formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};

    juce::IIRFilterAudioSource bass{&transportSource, false};
    juce::IIRFilterAudioSource high{&bass, false};
    juce::IIRFilterAudioSource mid{&high, false};

    double rate{};

    juce::ReverbAudioSource reverbSource{&resampleSource, false};
    juce::Reverb::Parameters reverbParameters;
};
