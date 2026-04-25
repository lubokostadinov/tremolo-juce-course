#pragma once

namespace tremolo {
class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
    void drawToggleButton(juce::Graphics&, juce::ToggleButton&, 
                          bool shouldDrawButtonAsHighLighted,
                          bool shouldDrawButtonAsDown) override;

    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height, 
                          float sliderPosProportional, float rotaryStartAngle,
                          float rotaryEndAngle, juce::Slider&) override;
    
    static juce::FontOptions getSideLabelsFont() {
        return interMedium().withPointHeight(10.f);
    }

private:
    static juce::FontOptions interMedium();
};
}  // namespace tremolo
