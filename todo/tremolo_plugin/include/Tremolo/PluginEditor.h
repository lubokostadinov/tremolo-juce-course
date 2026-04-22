#pragma once

namespace tremolo {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  void resized() override;

private:
  juce::ImageComponent background;
  juce::ImageComponent logo;

  juce::Slider rateSlider;
  juce::SliderParameterAttachment rateAttachment;
  
  LfoVisualizer lfoVisualizer;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
