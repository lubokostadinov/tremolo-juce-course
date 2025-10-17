#pragma once

namespace tremolo {
class AboutComponent : public juce::Component {
public:
  AboutComponent() {
    // popup.setAllowedPlacement(juce::BubbleComponent::BubblePlacement::below);
    // getParentComponent()->addAndMakeVisible(popup);
    // addChildComponent(popup);
  }

  void paint(juce::Graphics& g) override {
    g.setColour(juce::Colour{0xFF315160});
    constexpr auto thickness = 2.f;
    g.drawEllipse(getLocalBounds().toFloat().reduced(thickness), thickness);
    g.setFont(CustomLookAndFeel::getSideLabelsFont());
    g.drawFittedText("i", getLocalBounds(), juce::Justification::centred, 1);
  }

  void mouseEnter(const juce::MouseEvent& event) override {
    popup.reset(new juce::BubbleMessageComponent);
    popup->setAllowedPlacement(juce::BubbleComponent::BubblePlacement::below);
    popup->setAlwaysOnTop(true);
    popup->addToDesktop(0);

    juce::AttributedString text{"message"};
    text.setColour(juce::Colours::orange);
    text.setJustification(juce::Justification::centred);

    popup->showAt(this, text, 0, false);
  }

  void mouseExit(const juce::MouseEvent& event) override {
    popup->setVisible(false);
  }

private:
  std::unique_ptr<juce::BubbleMessageComponent> popup;
};
}  // namespace tremolo
