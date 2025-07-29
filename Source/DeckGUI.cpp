#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"
#include "LookAndFeel.h"

DeckGUI::DeckGUI(DJAudioPlayer *_player,
                 juce::AudioFormatManager &formatManagerToUse,
                 juce::AudioThumbnailCache &cacheToUse) : player(_player),
                                                          waveformDisplay(formatManagerToUse, cacheToUse)
{
    makeVisible();
    addListeners();
    setRanges();
    setValues();
    appearance();
    setLabels();

    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint(juce::Graphics &g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // clear the background

    // component outline
    g.setColour(juce::Colours::aliceblue);
    g.drawRect(getLocalBounds(), 1);

    // text color
    g.setColour(juce::Colour(211, 211, 211));
    g.setFont(14.0f);

    // background color
    g.fillAll(juce::Colour(60, 60, 60));
}

void DeckGUI::makeVisible()
{
    addAndMakeVisible(waveformDisplay);

    /* make buttons visible */
    addAndMakeVisible(loadButton);
    addAndMakeVisible(playButton);

    /* make sliders visible */
    addAndMakeVisible(posSlider);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(highSlider);
    addAndMakeVisible(midSlider);
    addAndMakeVisible(lowSlider);
    addAndMakeVisible(wetSlider);
    addAndMakeVisible(dampingSlider);
    addAndMakeVisible(roomSizeSlider);
    addAndMakeVisible(drySlider);
    addAndMakeVisible(freezeSlider);
    addAndMakeVisible(widthSlider);
}

void DeckGUI::addListeners()
{
    /* button listener */
    loadButton.addListener(this);
    playButton.addListener(this);

    /* slider listeners */
    posSlider.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    highSlider.addListener(this);
    midSlider.addListener(this);
    lowSlider.addListener(this);
    wetSlider.addListener(this);
    dampingSlider.addListener(this);
    roomSizeSlider.addListener(this);
    drySlider.addListener(this);
    freezeSlider.addListener(this);
    widthSlider.addListener(this);
}

/* assign slider range values */
void DeckGUI::setRanges()
{
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.01, 2.0);
    posSlider.setRange(0.0, 1.0);
    wetSlider.setRange(0.0, 1.0);
    dampingSlider.setRange(0.0, 1.0);
    roomSizeSlider.setRange(0.0, 1.0);
    drySlider.setRange(0.0, 1.0);
    freezeSlider.setRange(-100.0, 100.0);
    widthSlider.setRange(0.0, 1.0);
    highSlider.setRange(0.001, 2);
    midSlider.setRange(0.001, 2);
    lowSlider.setRange(0.001, 2);
}

/* initiralize slider values on launch */
void DeckGUI::setValues()
{
    volSlider.setValue(0.7);
    speedSlider.setValue(1.0);
    wetSlider.setValue(0.33f);
    dampingSlider.setValue(0.5f);
    roomSizeSlider.setValue(0.5f);
    drySlider.setValue(0.4f);
    freezeSlider.setValue(1.0f);
    widthSlider.setValue(1.0f);
    highSlider.setValue(1.0);
    midSlider.setValue(1.0);
    lowSlider.setValue(1.0);
}

void DeckGUI::appearance()
{
    /* look and feel */
    volSlider.setLookAndFeel(&linearSlider);
    speedSlider.setLookAndFeel(&linearSlider);
    posSlider.setLookAndFeel(&posLAF);
    wetSlider.setLookAndFeel(&rotaryLAF);
    dampingSlider.setLookAndFeel(&rotaryLAF);
    roomSizeSlider.setLookAndFeel(&rotaryLAF);
    drySlider.setLookAndFeel(&rotaryLAF);
    freezeSlider.setLookAndFeel(&rotaryLAF);
    widthSlider.setLookAndFeel(&rotaryLAF);
    highSlider.setLookAndFeel(&rotaryLAF);
    midSlider.setLookAndFeel(&rotaryLAF);
    lowSlider.setLookAndFeel(&rotaryLAF);

    /* remove number values */
    volSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    highSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    midSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    lowSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    posSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    speedSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    wetSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    dampingSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    roomSizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    drySlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    freezeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    widthSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    /* set slider styles */
    volSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    highSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    midSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    lowSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    posSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    wetSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    dampingSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    roomSizeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    drySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    freezeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    widthSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
}

/* make labels */
void DeckGUI::label(juce::String name, juce::Label &label)
{
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

/* assign label names */
void DeckGUI::setLabels()
{
    label("VOL", volLabel);
    label("HIGH", highLabel);
    label("MID", midLabel);
    label("LOW", lowLabel);
    label("SPEED", speedLabel);
    label("WET LEVEL", wetLabel);
    label("DAMPING", dampingLabel);
    label("ROOM SIZE", roomSizeLabel);
    label("DRY LEVEL", dryLabel);
    label("FREEZE", freezeLabel);
    label("WIDTH", widthLabel);

    label("", volValue);
    label("", highValue);
    label("", midValue);
    label("", lowValue);
    label("", speedValue);
    label("", wetValue);
    label("", dampingValue);
    label("", roomSizeValue);
    label("", dryValue);
    label("", freezeValue);
    label("", widthValue);
}

void DeckGUI::resized()
{
    double h = getHeight() / 31;
    double w = getWidth() / 19;

    loadButton.setBounds(0, 0, w * 2, h);
    playButton.setBounds(0, h, w * 2, h * 2);
    waveformDisplay.setBounds(w * 2, 0, w * 17, h * 3);

    volSlider.setBounds(0, h * 4, w * 2, h * 13);
    volLabel.setBounds(0, h * 17, w * 2, h);
    volValue.setBounds(0, h * 18, w * 2, h);

    highSlider.setBounds(w * 2, h * 6, w * 2, h * 2);
    highLabel.setBounds(w * 2, h * 8, w * 2, h);
    highValue.setBounds(w * 2, h * 9, w * 2, h);

    midSlider.setBounds(w * 2, h * 10, w * 2, h * 2);
    midLabel.setBounds(w * 2, h * 12, w * 2, h);
    highValue.setBounds(w * 2, h * 13, w * 2, h);

    lowSlider.setBounds(w * 2, h * 14, w * 2, h * 2);
    lowLabel.setBounds(w * 2, h * 16, w * 2, h);
    lowValue.setBounds(w * 2, h * 17, w * 2, h);

    posSlider.setBounds(w * 4, h * 4, w * 13, h * 15);

    speedSlider.setBounds((w * 17) - (w / 2), h * 10, w * 2, h * 7);
    speedLabel.setBounds((w * 17) - (w / 2), h * 17, w * 2, h);
    speedValue.setBounds((w * 17) - (w / 2), h * 18, w * 2, h);

    wetSlider.setBounds(w * 5, h * 20, w * 3, h * 3);
    wetLabel.setBounds(w * 5, h * 23, w * 3, h);
    wetValue.setBounds(w * 5, h * 24, w * 3, h);

    dampingSlider.setBounds(w * 9, h * 20, w * 3, h * 3);
    dampingLabel.setBounds(w * 9, h * 23, w * 3, h);
    dampingValue.setBounds(w * 9, h * 24, w * 3, h);

    roomSizeSlider.setBounds(w * 13, h * 20, w * 3, h * 3);
    roomSizeLabel.setBounds(w * 13, h * 23, w * 3, h);
    roomSizeValue.setBounds(w * 13, h * 24, w * 3, h);

    drySlider.setBounds(w * 5, h * 26, w * 3, h * 3);
    dryLabel.setBounds(w * 5, h * 29, w * 3, h);
    dryValue.setBounds(w * 5, h * 30, w * 3, h);

    freezeSlider.setBounds(w * 9, h * 26, w * 3, h * 3);
    freezeLabel.setBounds(w * 9, h * 29, w * 3, h);
    freezeValue.setBounds(w * 9, h * 30, w * 3, h);

    widthSlider.setBounds(w * 13, h * 26, w * 3, h * 3);
    widthLabel.setBounds(w * 13, h * 29, w * 3, h);
    widthValue.setBounds(w * 13, h * 30, w * 3, h);
}

/* button event listener */
void DeckGUI::buttonClicked(juce::Button *button)
{
    /* event listener for play button */
    if (button == &playButton)
    {
        /* check if file is loaded */
        if (isLoaded == false)
        {
            DBG("no file loaded");
            juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon, "No file loaded", "Please load audio file");
            return; // prevent further execution if no file is loaded
        }

        if (isLoaded)
        {
            /* changes play state */
            isPlaying = !isPlaying;

            /* if song is not playing*/
            if (isPlaying)
            {
                std::cout << "Playing song" << std::endl;
                player->start();
                playButton.setButtonText("STOP");
            }

            /* if song is playing */
            else if (!isPlaying)
            {
                std::cout << "Stopping song" << std::endl;
                player->stop();
                playButton.setButtonText("PLAY");
            }

            playButton.setToggleState(isPlaying, juce::NotificationType::dontSendNotification);
        }
    }

    /* event listener for load button */
    if (button == &loadButton)
    {
        auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser &chooser)
                             {
            player->loadURL(juce::URL{chooser.getResult()});
            waveformDisplay.loadURL(juce::URL{chooser.getResult()});
            
            /* resets play state when new file is uploaded */
            isPlaying = false;
            player->stop();
            playButton.setButtonText("PLAY");
            
            /* set load state */
            isLoaded = true;
            std::cout << "file loaded" << std::endl; });
    }
}

/* slider event listener */
void DeckGUI::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
        volValue.setText(juce::String(static_cast<int>(slider->getValue() * 100)) + "%", juce::dontSendNotification);
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
        speedValue.setText(juce::String(slider->getValue(), 2) + "x", juce::dontSendNotification);
    }

    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }

    if (slider == &wetSlider)
    {
        player->setWet(slider->getValue());
        wetValue.setText(juce::String(slider->getValue(), 2) + "f", juce::dontSendNotification);
    }

    if (slider == &dampingSlider)
    {
        player->setDamping(slider->getValue());
        dampingValue.setText(juce::String(slider->getValue(), 2) + "f", juce::dontSendNotification);
    }

    if (slider == &roomSizeSlider)
    {
        player->setRoomSize(slider->getValue());
        roomSizeValue.setText(juce::String(slider->getValue(), 2) + "f", juce::dontSendNotification);
    }

    if (slider == &drySlider)
    {
        player->setDry(slider->getValue());
        dryValue.setText(juce::String(slider->getValue(), 2) + "f", juce::dontSendNotification);
    }

    if (slider == &freezeSlider)
    {
        player->setFreeze(slider->getValue());
        freezeValue.setText(juce::String(slider->getValue(), 2) + "f", juce::dontSendNotification);
    }

    if (slider == &widthSlider)
    {
        player->setWidth(slider->getValue());
        widthValue.setText(juce::String(slider->getValue(), 2) + "f", juce::dontSendNotification);
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray &files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1)
    {
        // set state to true to enable playButton press
        isLoaded = true;
        player->loadURL(juce::URL{juce::File{files[0]}});
        waveformDisplay.loadURL(juce::URL{juce::File{files[0]}}); // Load into waveform display as well
    }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());

    /* updates slider position during playback */
    if (isPlaying)
    {
        posSlider.setValue(player->getPositionRelative());
    }
}
