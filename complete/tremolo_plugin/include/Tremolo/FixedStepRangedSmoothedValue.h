#pragma once

namespace tremolo {
template <typename FloatType>
class FixedStepRangedSmoothedValue
    : public juce::SmoothedValueBase<FixedStepRangedSmoothedValue<FloatType>> {
public:
  explicit FixedStepRangedSmoothedValue(
      juce::Range<FloatType> rangeToUse) noexcept
      : range{rangeToUse} {
    jassert(range.getStart() < range.getEnd());
    jassert(!juce::approximatelyEqual(range.getStart(), range.getEnd()));

    setCurrentAndTargetValueToExtreme(false);
  }

  void reset(double sampleRate, double rampLengthSeconds) noexcept {
    const auto rampLengthSamples =
        static_cast<int>(std::floor(rampLengthSeconds * sampleRate));
    step = range.getLength() / static_cast<FloatType>(rampLengthSamples);
  }

  void setTargetValueToExtreme(bool goToMax) noexcept {
    this->target = goToMax ? range.getEnd() : range.getStart();
    step =
        (this->currentValue < this->target) ? std::abs(step) : -std::abs(step);
    this->countdown =
        static_cast<int>(std::abs((this->currentValue - this->target) / step));
  }

  void setCurrentAndTargetValueToExtreme(bool setToMax) noexcept {
    this->setCurrentAndTargetValue(setToMax ? range.getEnd()
                                            : range.getStart());
  }

  FloatType getNextValue() noexcept {
    if (!this->isSmoothing()) {
      return this->target;
    }

    --(this->countdown);

    if (this->isSmoothing()) {
      this->currentValue += step;
    } else {
      this->currentValue = this->target;
    }

    return this->currentValue;
  }

  [[nodiscard]] juce::Range<FloatType> getRange() const noexcept {
    return range;
  }

private:
  juce::Range<FloatType> range;
  FloatType step{0.f};
};
}  // namespace tremolo
