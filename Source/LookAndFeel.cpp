#include "LookAndFeel.h"

rotaryLAF::rotaryLAF()
{
}

rotaryLAF::~rotaryLAF()
{
}

void rotaryLAF::drawRotarySlider(juce::Graphics &g,
                                 int x, int y,
                                 int width, int height,
                                 float sliderPos,
                                 float rotaryStartAngle, float rotaryEndAngle,
                                 juce::Slider &slider)
{
    float diameter = fmin(width, height);
    float radius = diameter / 2;
    float centreX = x + width / 2;
    float centreY = y + height / 2;
    float rx = centreX - radius;
    float ry = centreY - radius;
    auto angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

    // dial main body
    juce::ColourGradient gradient(juce::Colour(40, 40, 40), centreX, centreY,
                                  juce::Colour(25, 25, 25), centreX + radius, centreY + radius,
                                  false);
    g.setGradientFill(gradient);
    g.fillEllipse(rx, ry, diameter, diameter);
    juce::ColourGradient gradient2(juce::Colour(50, 50, 50), centreX, centreY,
                                   juce::Colour(40, 40, 40), centreX + radius, centreY + radius,
                                   false);
    g.setGradientFill(gradient2);
    g.fillEllipse(rx + radius / 2, ry + radius / 2, radius, radius);

    // dial tick
    juce::Path dialTick;
    float tickThickness = 3.0f;
    float innerOffset = 5.0f;
    dialTick.addEllipse(-tickThickness / 2, -radius + innerOffset, tickThickness, tickThickness);
    g.setColour(juce::Colour(211, 211, 211));
    g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centreX, centreY));
};

posLAF::posLAF()
{
}

posLAF::~posLAF()
{
}

void posLAF::drawRotarySlider(juce::Graphics &g,
                              int x, int y,
                              int width, int height,
                              float sliderPos,
                              float rotaryStartAngle, float rotaryEndAngle,
                              juce::Slider &slider)
{
    float diameter = fmin(width, height);
    float radius = diameter / 2;
    float centreX = x + width / 2;
    float centreY = y + height / 2;
    float rx = centreX - radius;
    float ry = centreY - radius;
    auto angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

    // dial main body
    juce::ColourGradient gradient(juce::Colour(40, 40, 40), centreX, centreY,
                                  juce::Colour(25, 25, 25), centreX + radius, centreY + radius,
                                  false);
    g.setGradientFill(gradient);
    g.fillEllipse(rx, ry, diameter, diameter);

    // music svg
    const auto svg = juce::Drawable::createFromImageData(BinaryData::musicalnotemusic_svg, BinaryData::musicalnotemusic_svgSize);
    juce::AffineTransform transform = juce::AffineTransform::scale(0.25f)               // scale down size of the svg
                                          .translated(centreX - (svg->getWidth() / 7),  // x position of the svg to center
                                                      centreY - (svg->getWidth() / 8)); // y position of the svg to center

    svg->setTransform(transform);
    svg->draw(g, 1.0);

    // dial tick
    juce::Path dialTick;
    float tickThickness = 5.0f;
    float tickOffset = tickThickness / 2;
    float centreOffset = radius * 0.85;

    dialTick.startNewSubPath(0.0f, -radius + 130.0f - centreOffset);
    dialTick.lineTo(-tickThickness, tickThickness - tickOffset - centreOffset);
    dialTick.lineTo(tickThickness, tickThickness - tickOffset - centreOffset);
    dialTick.closeSubPath();

    g.setColour(juce::Colours::aliceblue);
    g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centreX, centreY));
}

linearSlider::linearSlider()
{
}

linearSlider::~linearSlider()
{
}

void linearSlider::drawLinearSlider(juce::Graphics &g,
                                    int x, int y,
                                    int width, int height,
                                    float sliderPos,
                                    float minSliderPos, float maxSliderPos,
                                    juce::Slider::SliderStyle,
                                    juce::Slider &)
{
    float centreX = width / 2;
    float barWidth = width / 16;
    float barHeight = height;
    float fillHeight = sliderPos - barHeight;
    float knobWidth = barWidth * 3;
    float knobHeight = knobWidth / 2;

    // main slider color
    juce::Rectangle<float> body(centreX - barWidth / 2, 0, barWidth, barHeight);
    g.setColour(juce::Colour(120, 120, 120));
    g.fillRect(body);

    // filled slider color
    juce::Rectangle<float> fill(centreX - barWidth / 2, barHeight, barWidth, fillHeight);
    g.setColour(juce::Colour(25, 25, 25));
    g.fillRect(fill);

    // knob
    float knobLimit = juce::jlimit(0.0f, barHeight - knobHeight, sliderPos - knobHeight / 2);
    juce::Rectangle<float> knob(centreX - knobWidth / 2, knobLimit, knobWidth, knobHeight);
    g.setColour(juce::Colours::aliceblue);
    g.fillRect(knob);
}
