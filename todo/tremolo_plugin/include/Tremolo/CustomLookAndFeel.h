#pragma once

namespace tremolo {
class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
    void drawToggleButton(juce::Graphics&, juce::ToggleButton&, 
                          bool shouldDrawButtonAsHighLighted,
                          bool shouldDrawButtonAsDown) override;
};
}  // namespace tremolo
