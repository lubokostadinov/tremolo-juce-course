namespace tremolo {
PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p),
  rateAttachment{p.getParameterRefs().rate, rateSlider} {
  background.setImage(juce::ImageCache::getFromMemory(
      assets::Background_png, assets::Background_pngSize));

  logo.setImage(
      juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));

  addAndMakeVisible(background);
  addAndMakeVisible(logo);

  rateSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
  rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  rateSlider.setPopupDisplayEnabled(true, true, this);
  rateSlider.setTextValueSuffix(" Hz");
  addAndMakeVisible(rateSlider);

  addAndMakeVisible(lfoVisualizer);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(540, 270);
}

void PluginEditor::resized() {
  auto bounds = getLocalBounds();

  background.setBounds(bounds);

  //logo.setBounds({16, 16, 105, 24});
  logo.setBounds({0, 0, 0, 0});

  auto rateSliderBounds = bounds;
  rateSliderBounds.removeFromLeft(230);
  rateSliderBounds.removeFromRight(230);
  rateSliderBounds.removeFromTop(40);
  rateSliderBounds.removeFromBottom(150);
  rateSlider.setBounds(rateSliderBounds);

  lfoVisualizer.setBounds({18, 149, 504, 92});
}
}  // namespace tremolo
