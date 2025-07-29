#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "LookAndFeel.h"

class DeckGUI : public juce::Component,
                public juce::Button::Listener,
                public juce::Slider::Listener,
                public juce::FileDragAndDropTarget,
                public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer *player,
            juce::AudioFormatManager &formatManagerToUse,
            juce::AudioThumbnailCache &cacheToUse);
    ~DeckGUI();

    void paint(juce::Graphics &) override;
    void resized() override;

    void buttonClicked(juce::Button *) override;
    void sliderValueChanged(juce::Slider *slider) override;

    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped(const juce::StringArray &files, int x, int y) override;

    void timerCallback() override;

private:
    void makeVisible();
    void addListeners();
    void setRanges();
    void setValues();
    void setLabels();

    void appearance();
    rotaryLAF rotaryLAF;
    posLAF posLAF;
    linearSlider linearSlider;

    void label(juce::String name, juce::Label &label);

    bool isPlaying = false;
    bool isLoaded = false;

    /* declare buttons */
    juce::TextButton playButton{"PLAY"};
    juce::TextButton loadButton{"LOAD"};

    /* declare sliders */
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;
    juce::Slider highSlider;
    juce::Slider midSlider;
    juce::Slider lowSlider;
    juce::Slider wetSlider;
    juce::Slider dampingSlider;
    juce::Slider roomSizeSlider;
    juce::Slider drySlider;
    juce::Slider freezeSlider;
    juce::Slider widthSlider;

    /* declare labels*/
    juce::Label volLabel;
    juce::Label speedLabel;
    juce::Label highLabel;
    juce::Label midLabel;
    juce::Label lowLabel;
    juce::Label wetLabel;
    juce::Label dampingLabel;
    juce::Label roomSizeLabel;
    juce::Label dryLabel;
    juce::Label freezeLabel;
    juce::Label widthLabel;
    juce::Label volValue;
    juce::Label speedValue;
    juce::Label highValue;
    juce::Label midValue;
    juce::Label lowValue;
    juce::Label wetValue;
    juce::Label dampingValue;
    juce::Label roomSizeValue;
    juce::Label dryValue;
    juce::Label freezeValue;
    juce::Label widthValue;

    juce::FileChooser fChooser{"Select a file..."};

    WaveformDisplay waveformDisplay;
    DJAudioPlayer *player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
