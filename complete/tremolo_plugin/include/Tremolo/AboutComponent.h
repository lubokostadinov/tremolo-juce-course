#pragma once

namespace tremolo {
class AboutComponent : public juce::Component {
public:
  AboutComponent() = default;

  void paint(juce::Graphics& g) override {
    g.setColour(juce::Colour{0xFF315160});
    constexpr auto thickness = 2.f;
    g.drawEllipse(getLocalBounds().toFloat().reduced(thickness), thickness);
    g.setFont(CustomLookAndFeel::getSideLabelsFont());
    g.drawFittedText("i", getLocalBounds(), juce::Justification::centred, 1);
  }
};
}  // namespace tremolo
