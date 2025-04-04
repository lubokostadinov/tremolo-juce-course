#include "Tremolo/Parameters.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_core/juce_core.h>
#include <memory>

namespace ws {
namespace {
juce::AudioParameterFloat& createModulationRateParameter(
    Parameters::Container& c) {
  auto parameter = std::make_unique<juce::AudioParameterFloat>(
      "modulation.rate", "Modulation rate",
      juce::NormalisableRange<float>{0.1f, 20.f}, 5.f,
      juce::AudioParameterFloatAttributes{}.withLabel("Hz"));
  auto& parameterReference = *parameter;
  c.push_back(std::move(parameter));
  return parameterReference;
}

juce::AudioParameterBool& createBypassedParameter(Parameters::Container& c) {
  auto parameter = std::make_unique<juce::AudioParameterBool>(
      "bypassed", "Bypass", false,
      juce::AudioParameterBoolAttributes{}.withStringFromValueFunction(
          [](auto isBypassed, auto) { return isBypassed ? "Off" : "On"; }));
  auto& parameterReference = *parameter;
  c.push_back(std::move(parameter));
  return parameterReference;
}

juce::AudioParameterChoice& createWaveformParameter(Parameters::Container& c) {
  static const juce::StringArray choices{"Sine", "Triangle"};
  auto parameter = std::make_unique<juce::AudioParameterChoice>(
      "waveform", "Waveform", choices, 0,
      juce::AudioParameterChoiceAttributes{}.withLabel("Modulation waveform"));
  auto& parameterReference = *parameter;
  c.push_back(std::move(parameter));
  return parameterReference;
}
}  // namespace

Parameters::Parameters(Container& parameterContainer)
    : rate{createModulationRateParameter(parameterContainer)},
      bypassed{createBypassedParameter(parameterContainer)},
      waveform{createWaveformParameter(parameterContainer)} {}
}  // namespace ws
