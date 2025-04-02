#pragma once
#include <juce_dsp/juce_dsp.h>
#include <ranges>

namespace ws {
template <typename SampleType>
class Tremolo {
public:
  Tremolo() : lfo{[](SampleType phase) { return std::sin(phase); }} {}

  template <typename ProcessContext>
  void process(const ProcessContext& context) noexcept {
    const auto& inputBlock = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();

    // sanity check
    jassert(inputBlock.getNumSamples() == outputBlock.getNumSamples());
    jassert(inputBlock.getNumChannels() == outputBlock.getNumChannels());

    // for each sample
    for (const auto i :
         std::views::iota(0, static_cast<int>(inputBlock.getNumSamples()))) {
      // generate the LFO value
      const auto lfoValue = lfo.processSample(SampleType(0));
      // calculate the modulation value
      const auto modulationValue =
          (SampleType(1) + MODULATION_DEPTH * lfoValue);

      for (const auto channel :
           std::views::iota(0, static_cast<int>(inputBlock.getNumChannels()))) {
        // get the input sample
        const auto inputSample = inputBlock.getSample(channel, i);

        // modulate the sample
        const auto outputSample = modulationValue * inputSample;

        // set the output sample
        outputBlock.setSample(channel, i, outputSample);
      }
    }
  }

private:
  static constexpr auto MODULATION_DEPTH = SampleType(0.1);
  juce::dsp::Oscillator<SampleType> lfo;
};
}  // namespace ws
