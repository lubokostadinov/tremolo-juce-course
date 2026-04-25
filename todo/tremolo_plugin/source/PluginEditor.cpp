namespace tremolo {
PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p),
  waveformAttachment{p.getParameterRefs().waveform, waveformComboBox},
  rateAttachment{p.getParameterRefs().rate, rateSlider},
  bypassAttachment{p.getParameterRefs().bypassed, bypassButton} {

  background.setImage(juce::ImageCache::getFromMemory(assets::Background_png, assets::Background_pngSize));
  logo.setImage(juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));

  addAndMakeVisible(background);
  addAndMakeVisible(logo);

  waveformLabel.setFont(lookAndFeel.getSideLabelsFont());
  addAndMakeVisible(waveformLabel);

  waveformComboBox.addItemList(p.getParameterRefs().waveform.choices, 1);
  waveformAttachment.sendInitialUpdate();
  addAndMakeVisible(waveformComboBox);

  rateSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
  rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  rateSlider.setPopupDisplayEnabled(true, true, this);
  rateSlider.setTextValueSuffix(" Hz");
  addAndMakeVisible(rateSlider);

  rateLabel.setInterceptsMouseClicks(false, false);
  addAndMakeVisible(rateLabel);

  bypassButton.onClick = [this] () {
    bypassButton.setButtonText(bypassButton.getToggleState() ? "Bypassed" : "Off");
  };
  bypassButton.onClick();
  addAndMakeVisible(bypassButton);

  addAndMakeVisible(lfoVisualizer);

  setLookAndFeel(&lookAndFeel);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(540, 270);
}

PluginEditor::~PluginEditor() {
  setLookAndFeel(nullptr);
}

void PluginEditor::resized() {
  auto bounds = getLocalBounds();

  background.setBounds(bounds);

  logo.setBounds({0, 0, 0, 0});

  auto rateSliderBounds = bounds;
  rateSliderBounds.removeFromLeft(230);
  rateSliderBounds.removeFromRight(230);
  rateSliderBounds.removeFromTop(40);
  rateSliderBounds.removeFromBottom(150);
  rateSlider.setBounds(rateSliderBounds);

  rateLabel.setJustificationType(juce::Justification::centred);
  rateLabel.setBounds(rateSliderBounds);

  auto buttonBounds = bounds;
  buttonBounds.removeFromLeft(392);
  buttonBounds.removeFromRight(16);
  buttonBounds.removeFromTop(66);
  buttonBounds.removeFromBottom(176);
  bypassButton.setBounds(buttonBounds);

  auto waveformComboBoxBounds = bounds;
  waveformComboBoxBounds.removeFromLeft(16);
  waveformComboBoxBounds.removeFromRight(392);
  waveformComboBoxBounds.removeFromTop(66);
  waveformComboBoxBounds.removeFromBottom(176);
  waveformComboBox.setBounds(waveformComboBoxBounds);

  const auto waveformLabelBounds = waveformComboBoxBounds.translated(0, -waveformComboBoxBounds.getHeight());
  waveformLabel.setBounds(waveformLabelBounds);

  lfoVisualizer.setBounds({18, 149, 504, 92});
}
}  // namespace tremolo
