#pragma once

namespace tremolo {
class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
    void drawToggleButton(juce::Graphics&, juce::ToggleButton&, 
                          bool shouldDrawButtonAsHighLighted,
                          bool shouldDrawButtonAsDown) override;
    
    static juce::FontOptions getSideLabelsFont() {
        return interMedium().withPointHeight(10.f);
    }

private:
    static juce::FontOptions interMedium();
};
}  // namespace tremolo
