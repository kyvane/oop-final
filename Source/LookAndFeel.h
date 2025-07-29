#pragma once
#include <../JuceLibraryCode/JuceHeader.h>

class rotaryLAF : public juce::LookAndFeel_V4
{
public:
    rotaryLAF();
    ~rotaryLAF();

    void drawRotarySlider(juce::Graphics &g,
                          int x, int y,
                          int width, int height,
                          float sliderPos,
                          float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider &slider) override;
};

class posLAF : public juce::LookAndFeel_V4
{
public:
    posLAF();
    ~posLAF();

    void drawRotarySlider(juce::Graphics &g,
                          int x, int y,
                          int width, int height,
                          float sliderPos,
                          float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider &slider) override;
};

class linearSlider : public juce::LookAndFeel_V4
{
public:
    linearSlider();
    ~linearSlider();

    void drawLinearSlider(juce::Graphics &g,
                          int x, int y,
                          int width, int height,
                          float sliderPos,
                          float minSliderPos, float maxSliderPos,
                          juce::Slider::SliderStyle,
                          juce::Slider &slider) override;
};
