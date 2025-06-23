
namespace tremolo {
namespace {
template <typename Param>
Param& addParamToProcessor(juce::AudioProcessor& processor,
                           std::unique_ptr<Param> param) {
  auto& result = *param;
  processor.addParameter(param.release());
  return result;
}

juce::AudioParameterFloat& createModulationRateParameter(
    juce::AudioProcessor& c) {
  constexpr auto versionHint = 1;
  return addParamToProcessor(
      c,
      std::make_unique<juce::AudioParameterFloat>(
          juce::ParameterID{"modulation.rate", versionHint}, "Modulation rate",
          juce::NormalisableRange<float>{0.1f, 20.f, 0.01f, 0.4f}, 5.f,
          juce::AudioParameterFloatAttributes{}.withLabel("Hz")));
}

juce::AudioParameterBool& createBypassedParameter(juce::AudioProcessor& c) {
  constexpr auto versionHint = 1;
  return addParamToProcessor(
      c, std::make_unique<juce::AudioParameterBool>(
             juce::ParameterID{"bypassed", versionHint}, "Bypass", false));
}

juce::AudioParameterChoice& createWaveformParameter(juce::AudioProcessor& c) {
  constexpr auto versionHint = 1;
  return addParamToProcessor(
      c, std::make_unique<juce::AudioParameterChoice>(
             juce::ParameterID{"modulation.waveform", versionHint},
             "Modulation waveform", juce::StringArray{"Sine", "Triangle"}, 0));
}
}  // namespace

Parameters::Parameters(juce::AudioProcessor& parameterContainer)
    : rate{createModulationRateParameter(parameterContainer)},
      bypassed{createBypassedParameter(parameterContainer)},
      waveform{createWaveformParameter(parameterContainer)} {}
}  // namespace tremolo
