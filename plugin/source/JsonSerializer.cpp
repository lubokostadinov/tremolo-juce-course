#include "Tremolo/JsonSerializer.h"
#include <juce_core/juce_core.h>

namespace {
constexpr auto pluginName = "pluginName";
}

template <>
struct juce::SerialisationTraits<ws::Parameters> {
  static constexpr auto marshallingVersion = 1;

  template <typename Archive, typename T>
  static void serialise(Archive& archive, T& t) {
    using namespace juce;

    archive(named(pluginName, JucePlugin_Name),
            named("modulationRateHz", t.rate.get()),
            named("bypassed", t.bypassed.get()),
            named("modulationWaveform", t.waveform.getCurrentChoiceName()));
  }
};

namespace ws {
void JsonSerializer::serialize(const Parameters& parameters,
                               juce::OutputStream& output) {
  const auto json = juce::ToVar::convert(parameters);

  if (!json.has_value()) {
    return;
  }

  jassert(json->isObject());

  json->getDynamicObject()->writeAsJSON(
      output, juce::JSON::FormatOptions{}
                  .withSpacing(juce::JSON::Spacing::multiLine)
                  .withMaxDecimalPlaces(2));
}

void JsonSerializer::deserialize(juce::InputStream& input,
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

  if (!parsedResult.hasProperty("pluginName") ||
      parsedResult["pluginName"] != JucePlugin_Name) {
    DBG("invalid plugin name");
    return;
  }

  constexpr auto currentVersion = 1;
  if (!parsedResult.hasProperty("__version__") ||
      parsedResult["__version__"] != juce::var{currentVersion}) {
    DBG("this plugin version only supports version " << currentVersion
                                                     << " of parameters");
    return;
  }

  parameters.rate = parsedResult.getProperty(
      "modulationRateHz", static_cast<double>(parameters.rate.get()));
  parameters.bypassed =
      parsedResult.getProperty("bypassed", parameters.bypassed.get());

  if (parsedResult.hasProperty("modulationWaveform")) {
    const auto waveformName = parsedResult["modulationWaveform"];
    if (waveformName.isString()) {
      const auto index =
          parameters.waveform.choices.indexOf(waveformName.toString());
      if (0 <= index) {
        parameters.waveform = index;
      }
    }
  }
}
}  // namespace ws
