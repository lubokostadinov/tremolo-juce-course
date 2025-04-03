#pragma once
#include <juce_dsp/juce_dsp.h>
#include <ranges>
#include <array>

namespace ws {
template <typename SampleType>
class Tremolo {
public:
  enum LfoWaveform : size_t {
    SINE = 0u,
    TRIANGLE = 1u,
    COUNT = 2u,
  };

  Tremolo()
      : lfos{juce::dsp::Oscillator<SampleType>{
                 [](SampleType phase) { return std::sin(phase); }},
             juce::dsp::Oscillator<SampleType>{[](SampleType) { return 0; }}} {
    std::ranges::for_each(
        lfos, [](auto& lfo) { lfo.setFrequency(SampleType(5), true); });
  }

  void prepare(double sampleRate) noexcept {
    std::ranges::for_each(lfos, [spec = juce::dsp::ProcessSpec{
                                     .sampleRate = sampleRate,
                                     .maximumBlockSize = 1u,
                                     .numChannels = 1u,
                                 }](auto& lfo) { lfo.prepare(spec); });
  }

  void setModulationRate(SampleType rateHz) noexcept {
    std::ranges::for_each(lfos,
                          [rateHz](auto& lfo) { lfo.setFrequency(rateHz); });
  }

  void setLfoWaveform(LfoWaveform waveform) {
    jassert(waveform < LfoWaveform::COUNT);

    if (waveform < LfoWaveform::COUNT) {
      currentLfo = waveform;
    }
  }

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
      // generate the LFO value;
      // the argument is added to the generated sample, thus, we pass in 0
      const auto lfoValue = lfos[currentLfo].processSample(SampleType(0));
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

  void reset() noexcept {
    std::ranges::for_each(lfos, [](auto& lfo) { lfo.reset(); });
  }

private:
  static constexpr auto MODULATION_DEPTH = SampleType(0.1);
  std::array<juce::dsp::Oscillator<SampleType>, LfoWaveform::COUNT> lfos;
  size_t currentLfo = LfoWaveform::SINE;
};
}  // namespace ws
