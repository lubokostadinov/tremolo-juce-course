#pragma once

namespace tremolo {
class BypassTransitionSmoother {
public:
  void prepare(int channelCount, int expectedMaxFramesPerBlock) {
    dryBuffer.setSize(channelCount, expectedMaxFramesPerBlock);
    reset();
  }

  void setBypass(bool bypass) {
    if (bypass != isBypassed) {
      isTransition = true;
    }

    isBypassed = bypass;
  }

  [[nodiscard]] bool isTransitioning() const noexcept { return isTransition; }

  void setDryBuffer(const juce::AudioBuffer<float>& buffer) {
    if (!isTransitioning()) {
      return;
    }

    const auto startDryGain = isBypassed ? 0.f : 1.f;
    const auto endDryGain = 1.f - startDryGain;

    jassert(buffer.getNumSamples() <= dryBuffer.getNumSamples());
    jassert(buffer.getNumChannels() <= dryBuffer.getNumChannels());

    for (const auto channel : std::views::iota(0, buffer.getNumChannels())) {
      dryBuffer.copyFromWithRamp(channel, 0, buffer.getReadPointer(channel),
                                 buffer.getNumSamples(), startDryGain,
                                 endDryGain);
    }
  }

  void mixToWetBuffer(juce::AudioBuffer<float>& buffer) {
    if (!isTransitioning()) {
      return;
    }

    jassert(buffer.getNumSamples() <= dryBuffer.getNumSamples());
    jassert(buffer.getNumChannels() <= dryBuffer.getNumChannels());

    const auto startWetGain = isBypassed ? 1.f : 0.f;
    const auto endWetGain = 1.f - startWetGain;
    for (const auto channel : std::views::iota(0, buffer.getNumChannels())) {
      buffer.applyGainRamp(channel, 0, buffer.getNumSamples(), startWetGain,
                           endWetGain);
      buffer.addFrom(channel, 0, dryBuffer, channel, 0, buffer.getNumSamples());
    }

    isTransition = false;
  }

  void reset() {
    isBypassed = false;
    isTransition = false;
    dryBuffer.clear();
  }

private:
  bool isBypassed = false;
  bool isTransition = false;
  juce::AudioBuffer<float> dryBuffer;
};
}  // namespace tremolo