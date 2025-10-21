#pragma once

namespace tremolo {
class About : private juce::MouseListener {
public:
  About(juce::Component& clickTarget) : target{clickTarget} {
    popup.setAllowedPlacement(juce::BubbleComponent::BubblePlacement::below);
    popup.setAlwaysOnTop(true);

    text.setColour(
        CustomLookAndFeel::getColor(CustomLookAndFeel::Colors::paleBlue));
    text.setJustification(juce::Justification::centred);

    target.addMouseListener(this, true);
  }

  ~About() override { target.removeMouseListener(this); }

  void mouseDown(const juce::MouseEvent&) override {
    if (popup.getParentComponent() == nullptr) {
      if (auto* parent = target.getParentComponent()) {
        parent->addChildComponent(popup);
      } else {
        DBG("Cannot display the popup; no parent of the target.");
        jassertfalse;
      }
    }

    if (!popup.isVisible()) {
      popup.showAt(&target, text, 0, true);
    }
  }

private:
  juce::Component& target;
  juce::BubbleMessageComponent popup;
  juce::AttributedString text{JucePlugin_Manufacturer
                              "\n" JucePlugin_Name "\n" __DATE__ " " __TIME__
                              "\nv" JucePlugin_VersionString};

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(About)
};
}  // namespace tremolo
