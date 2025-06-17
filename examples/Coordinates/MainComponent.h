#include <juce_gui_basics/juce_gui_basics.h>

class MainComponent : public juce::Component {
public:
  MainComponent() { setBounds(0, 0, 400, 300); }

  void paint(juce::Graphics& g) override { g.fillAll(juce::Colours::orange); }
};