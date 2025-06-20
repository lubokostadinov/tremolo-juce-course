#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class LongRunningTask : public juce::Component {
public:
  LongRunningTask() {
    addAndMakeVisible(startButton);
    addAndMakeVisible(progressBar);
    addAndMakeVisible(resultLabel);

    setSize(500, 300);
  }

  void resized() override {
    auto bounds = getLocalBounds();

    startButton.setBounds(bounds.removeFromTop(100).reduced(20));
    progressBar.setBounds(bounds.removeFromTop(100).reduced(20));
    resultLabel.setBounds(bounds.removeFromTop(100).reduced(20));
  }



private:
  juce::TextButton startButton{"Click to start looking for prime numbers"};
  double progress{0.0};
  juce::ProgressBar progressBar{progress, juce::ProgressBar::Style::linear};
  juce::Label resultLabel{"result label", "Here, the result should appear"};
};

using MainComponent = LongRunningTask;
