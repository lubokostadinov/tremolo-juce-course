#pragma once

namespace tremolo {
class About : private juce::MouseListener {
public:
  About(juce::Component& clickTarget, juce::String messageOnClick)
      : target{clickTarget}, message{std::move(messageOnClick)} {
    popup.setAllowedPlacement(juce::BubbleComponent::BubblePlacement::below);
    popup.setAlwaysOnTop(true);

    message.setColour(
        CustomLookAndFeel::getColor(CustomLookAndFeel::Colors::paleBlue));
    message.setJustification(juce::Justification::centred);

    target.addMouseListener(this, true);
  }

  ~About() override { target.removeMouseListener(this); }

  void mouseDown(const juce::MouseEvent&) override { displayPopup(); }

private:
  void displayPopup() {
    addPopupToTargetParent();

    if (!popup.isVisible()) {
      popup.showAt(&target, message, 0, true);
    }
  }

  void addPopupToTargetParent() {
    if (popup.getParentComponent() == nullptr) {
      if (auto* parent = target.getParentComponent()) {
        parent->addChildComponent(popup);
      } else {
        DBG("Cannot display the popup; no parent of the target.");
        jassertfalse;
      }
    }
  }

  juce::Component& target;
  juce::AttributedString message;
  juce::BubbleMessageComponent popup;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(About)
};
}  // namespace tremolo
