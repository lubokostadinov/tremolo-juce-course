#include "Tremolo/JSONSerializer.h"
#include <juce_core/juce_core.h>

namespace ws {
namespace {
struct ParameterIdentifiers {
  juce::Identifier pluginName;

  /** @brief Version of the parameters JSON */
  juce::Identifier version;

  /** @brief Modulation rate parameter */
  juce::Identifier rate;

  /** @brief Bypass parameter */
  juce::Identifier bypass;
};

const ParameterIdentifiers& getIdentifiers() {
  static const ParameterIdentifiers ids{
      .pluginName = "pluginName",
      .version = "version",
      .rate = "modulationRateHz",
      .bypass = "bypassed",
  };
  return ids;
}

constexpr auto PLUGIN_NAME = JucePlugin_Name;
constexpr auto CURRENT_VERSION = "1.0.0";
}  // namespace

void JSONSerializer::serialize(const Parameters& parameters,
                               juce::OutputStream& output) {
  juce::DynamicObject json{};
  const auto& ids = getIdentifiers();

  json.setProperty(ids.pluginName, PLUGIN_NAME);
  json.setProperty(ids.version, CURRENT_VERSION);
  json.setProperty(ids.rate, double(parameters.rate));
  json.setProperty(ids.bypass, bool{parameters.bypassed});

  json.writeAsJSON(output, juce::JSON::FormatOptions{}
                               .withSpacing(juce::JSON::Spacing::multiLine)
                               .withMaxDecimalPlaces(2));
}
}  // namespace ws
