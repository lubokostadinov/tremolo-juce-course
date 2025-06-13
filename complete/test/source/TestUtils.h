#pragma once
#include <juce_core/juce_core.h>

namespace tremolo {
inline std::string getFileOutputPath(juce::StringRef filename) {
  return juce::File::getSpecialLocation(
             juce::File::SpecialLocationType::currentExecutableFile)
      .getParentDirectory()
      .getChildFile(filename)
      .getFullPathName()
      .toStdString();
}
}  // namespace tremolo
