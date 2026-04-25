#pragma once

namespace tremolo {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);
  ~PluginEditor() override;

  void resized() override;

private:
  juce::ImageComponent background;
  juce::ImageComponent logo;

  juce::Label waveformLabel{"waveform label", "Waveform"};
  juce::ComboBox waveformComboBox;
  juce::ComboBoxParameterAttachment waveformAttachment;

  juce::Label rateLabel{"rate label", "Rate"};
  RateSlider rateSlider;
  juce::SliderParameterAttachment rateAttachment;

  juce::ToggleButton bypassButton{"Bypassed"};
  juce::ButtonParameterAttachment bypassAttachment;

  CustomLookAndFeel lookAndFeel;

  LfoVisualizer lfoVisualizer;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
