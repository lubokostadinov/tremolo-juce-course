#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <bit>

class GuiThreadIdPrinting : public juce::Component {
public:
  GuiThreadIdPrinting() {
    const auto threadId = juce::String::toHexString(
        std::bit_cast<juce::int64>(juce::Thread::getCurrentThreadId()));

    DBG("Main component constructor thread ID: " << threadId);
  }
};

using MainComponent = GuiThreadIdPrinting;
