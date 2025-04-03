#include <Tremolo/JSONSerializer.h>
#include <gtest/gtest.h>
#include <juce_core/juce_core.h>
#include "Tremolo/Parameters.h"

namespace ws {
TEST(JSONSerializer, SerializeToFile) {
  Parameters::Container container;
  Parameters parameters{container};

  parameters.rate = 10.f;
  parameters.bypassed = true;

  juce::FileOutputStream outputStream{
      juce::File::getSpecialLocation(
          juce::File::SpecialLocationType::currentExecutableFile)
          .getParentDirectory()
          .getChildFile("SerializedParameters.json")};
  ASSERT_TRUE(outputStream.openedOk());
  outputStream.setPosition(0);
  outputStream.truncate();

  JSONSerializer{}.serialize(parameters, outputStream);
  outputStream.flush();
}

TEST(JSONSerializer, DeserializeFromString) {
  const juce::String SAVED_PARAMETERS =
      u8R"({
  "pluginName": "Tremolo",
  "version": "1.0.0",
  "modulationRateHz": 10.0,
  "bypassed": true
})";

  Parameters::Container container;
  Parameters parameters{container};

  DBG(SAVED_PARAMETERS);
  juce::MemoryInputStream inputStream{
      SAVED_PARAMETERS.getCharPointer(),
      static_cast<size_t>(SAVED_PARAMETERS.length()), false};

  JSONSerializer{}.deserialize(inputStream, parameters);

  EXPECT_FLOAT_EQ(parameters.rate, 10.f);
  EXPECT_TRUE(parameters.bypassed);
}
}  // namespace ws
