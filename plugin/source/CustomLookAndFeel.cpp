#include "Tremolo/CustomLookAndFeel.h"

namespace ws {
CustomLookAndFeel::CustomLookAndFeel() {
  setColour(juce::TextButton::buttonOnColourId, getColour<Colours::ORANGE>());
  setColour(juce::TextButton::buttonColourId, getColour<Colours::LIGHT_GREY>());
}

void CustomLookAndFeel::drawComboBox(juce::Graphics& g,
                                     int width,
                                     int height,
                                     bool /* isButtonDown */,
                                     int /* buttonX */,
                                     int /* buttonY */,
                                     int /* buttonW */,
                                     int /* buttonH */,
                                     juce::ComboBox& box) {
  auto cornerSize =
      box.findParentComponentOfClass<juce::ChoicePropertyComponent>() != nullptr
          ? 0.0f
          : 3.0f;
  juce::Rectangle<int> boxBounds(0, 0, width, height);

  g.setColour(box.findColour(juce::ComboBox::backgroundColourId));
  g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

  g.setColour(box.findColour(juce::ComboBox::outlineColourId));
  g.drawRoundedRectangle(boxBounds.toFloat().reduced(0.5f, 0.5f), cornerSize,
                         1.0f);

  auto arrowZone = juce::Rectangle<int>(width - 30, 0, 20, height).toFloat();
  juce::Path path;
  path.startNewSubPath(arrowZone.getX() + 3.0f, arrowZone.getCentreY() - 2.0f);
  path.lineTo(arrowZone.getCentreX(), arrowZone.getCentreY() + 3.0f);
  path.lineTo(arrowZone.getRight() - 3.0f, arrowZone.getCentreY() - 2.0f);

  g.setColour(box.findColour(juce::ComboBox::arrowColourId)
                  .withAlpha((box.isEnabled() ? 0.9f : 0.2f)));
  g.strokePath(path, juce::PathStrokeType(2.0f));
}
}  // namespace ws
