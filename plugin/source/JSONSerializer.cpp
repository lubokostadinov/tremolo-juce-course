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
  json.setProperty(ids.rate, static_cast<double>(parameters.rate.get()));
  json.setProperty(ids.bypass, parameters.bypassed.get());

  json.writeAsJSON(output, juce::JSON::FormatOptions{}
                               .withSpacing(juce::JSON::Spacing::multiLine)
                               .withMaxDecimalPlaces(2));
}

void JSONSerializer::deserialize(juce::InputStream& input,
                                 Parameters& parameters) {
  juce::var parsedResult;
  const auto parsingResult =
      juce::JSON::parse(input.readEntireStreamAsString(), parsedResult);

  if (parsingResult.failed()) {
    DBG(parsingResult.getErrorMessage());
    return;
  }

  if (!parsedResult.isObject()) {
    DBG("not a dynamic object");
    return;
  }

  const auto& ids = getIdentifiers();
  if (!parsedResult.hasProperty(ids.pluginName) ||
      parsedResult[ids.pluginName] != PLUGIN_NAME) {
    DBG("invalid plugin name");
    return;
  }

  if (!parsedResult.hasProperty(ids.version) ||
      parsedResult[ids.version] != CURRENT_VERSION) {
    DBG("this plugin version only supports version 1.0.0 of parameters");
    return;
  }

  parameters.rate = parsedResult.getProperty(
      ids.rate, static_cast<double>(parameters.rate.get()));
  parameters.bypassed =
      parsedResult.getProperty(ids.bypass, parameters.bypassed.get());
}
}  // namespace ws
