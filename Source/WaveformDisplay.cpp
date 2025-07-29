#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(juce::AudioFormatManager &formatManagerToUse,
                                 juce::AudioThumbnailCache &cacheToUse) : audioThumb(1000, formatManagerToUse, cacheToUse),
                                                                          fileLoaded(false),
                                                                          position(0)
{
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint(juce::Graphics &g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // clear the background

    /* component outline */
    g.setColour(juce::Colours::purple);
    g.drawRect(getLocalBounds(), 1);

    /* background color */
    g.fillAll(juce::Colour(60, 60, 60));

    /* waveform & text color */
    g.setColour(juce::Colour(220, 20, 60));

    if (fileLoaded)
    {
        /* draw waveform */
        audioThumb.drawChannel(g,
                               getLocalBounds(),
                               0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f);

        /* draw waveform position */
        g.setColour(juce::Colours::aliceblue);
        g.drawRect(position * getWidth(), 0, getWidth() / 50, getHeight());
    }
    else
    {
        /* placeholder text */
        g.setFont(20.0f);
        g.drawText("File not loaded...", getLocalBounds(),
                   juce::Justification::centred, true);
    }
}

void WaveformDisplay::resized()
{
}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
    audioThumb.clear(); // clears existing waveform
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
    if (fileLoaded)
    {
        /* generate waveform */
        std::cout << "wfd: loaded! " << std::endl;
        repaint();
    }
    else
    {
        std::cout << "wfd: not loaded! " << std::endl;
    }
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    std::cout << "wfd: change received! " << std::endl;

    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position)
    {
        position = pos;
        repaint();
    }
}
