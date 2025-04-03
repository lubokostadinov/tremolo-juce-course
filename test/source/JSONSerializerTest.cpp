#include <Tremolo/JSONSerializer.h>
#include <gtest/gtest.h>
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
}  // namespace ws
