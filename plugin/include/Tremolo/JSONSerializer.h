#pragma once

#include <juce_core/juce_core.h>
#include "Parameters.h"

namespace ws {
class JSONSerializer {
public:
  void serialize(const Parameters&, juce::OutputStream&);
};
}  // namespace ws
