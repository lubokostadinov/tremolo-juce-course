#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace ws {
class CustomLookAndFeel : public juce::LookAndFeel_V4 {
private:
  const auto& getColourPalette() {
    static const std::array COLOURS{
        juce::Colour{0xFFEF7600},
        juce::Colour{0xFFD9D9D9},
    };
    return COLOURS;
  }

public:
  enum Colours : size_t { ORANGE, LIGHT_GREY };

  CustomLookAndFeel();

  template <Colours ColourName>
  const juce::Colour& getColour() {
    return std::get<ColourName>(getColourPalette());
  }
};
}  // namespace ws
