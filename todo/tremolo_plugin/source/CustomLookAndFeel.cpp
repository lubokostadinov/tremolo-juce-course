namespace tremolo {
void CustomLookAndFeel::drawToggleButton(juce::Graphics& g,
                                         juce::ToggleButton& button, 
                                         bool shouldDrawButtonAsHighLighted,
                                         bool shouldDrawButtonAsDown) {
    const auto bounds = button.getLocalBounds().reduced(2);

    if (button.getToggleState()) {
        auto buttonGradient = juce::ColourGradient::vertical(juce::Colour{0xffff901a},
                                                             juce::Colour{0xffffc300},
                                                             bounds);
        
        g.setGradientFill(buttonGradient);
        g.fillRoundedRectangle(bounds.toFloat(), 4.f);
        
        g.setColour(juce::Colour{0xff501a0b});
    }
    else {
        auto buttonGradient = juce::ColourGradient::vertical(juce::Colour{0xff4a7090},
                                                             juce::Colour{0xff324358},
                                                             bounds);

        buttonGradient.addColour(0.73, juce::Colour{0xff315160});
        g.setGradientFill(buttonGradient);
        g.fillRoundedRectangle(bounds.toFloat(), 4.f);

        g.setColour(juce::Colour{0xffddecff});
    }

    g.setFont(interMedium().withPointHeight(12.f));

    DBG(g.getCurrentFont().getTypefacePtr()->getName());
    
    g.drawText(button.getButtonText(), bounds, juce::Justification::centred, false);
}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, 
                                         float sliderPosProportional, float rotaryStartAngle,
                                         float rotaryEndAngle, juce::Slider&) {

    auto bounds = juce::Rectangle{x, y, width, height}.toFloat().reduced(3.75f);
    g.setColour(juce::Colour{0xff2a3a3b});
    g.fillEllipse(bounds);

    auto toAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    juce::Path valueArc;
    valueArc.addPieSegment(bounds.reduced(0.25f), rotaryStartAngle, toAngle, 0);
            
    g.setColour(juce::Colours::orange);
    g.fillPath(valueArc);
}

juce::FontOptions CustomLookAndFeel::interMedium() {
    static const auto result = juce::FontOptions{juce::Typeface::createSystemTypefaceFor(
                               assets::InterMedium_ttf, assets::InterMedium_ttfSize)};

    return juce::FontOptions{result};
}

}  // namespace tremolo
