#include <gtest/gtest.h>
#include <juce_dsp/juce_dsp.h>
#include "Tremolo/Tremolo.h"

#include <wolfsound/file/wolfsound_WavFileWriter.hpp>

namespace ws {
TEST(Tremolo, ExtractLfo) {
  Tremolo testee;
  constexpr auto sampleRate = 48000.0;
  testee.prepare(sampleRate);

  testee.setModulationRate(1.f);

  juce::AudioBuffer<float> buffer;
  buffer.setSize(1, int(sampleRate));

  juce::dsp::AudioBlock<float> block{buffer};
  block.fill(1.f);
  testee.process(buffer);
  block.subtract(1.f);

  wolfsound::WavFileWriter::writeToFile(
      juce::File::getSpecialLocation(
          juce::File::SpecialLocationType::currentExecutableFile)
          .getParentDirectory()
          .getChildFile("1_Hz_LFO.wav")
          .getFullPathName()
          .toStdString(),
      std::vector<float>(block.getChannelPointer(0u),
                         block.getChannelPointer(0u) + block.getNumSamples()),
      wolfsound::Frequency{sampleRate});
}
}  // namespace ws
