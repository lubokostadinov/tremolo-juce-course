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
    g.drawText(button.getButtonText(), bounds, juce::Justification::centred, false);
}

}  // namespace tremolo
