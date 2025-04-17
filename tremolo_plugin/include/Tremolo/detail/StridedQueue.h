namespace ws::detail {
template <size_t Size>
class StridedQueue {
public:
  StridedQueue() { stridedElements.resize(Size, 0.f); }

  void setStride(int newStride) {
    jassert(newStride > 0);

    stride = newStride;
  }

  [[nodiscard]] size_t size() const noexcept { return stridedElements.size(); }

  float& front() noexcept { return stridedElements.front(); }

  float& at(size_t index) { return stridedElements.at(index); }

  void pushBack(const juce::AudioBuffer<float>& buffer) {
    for (; elementIndex < buffer.getNumSamples(); elementIndex += stride) {
      const auto sample = buffer.getSample(0, elementIndex);
      stridedElements.pop_front();
      stridedElements.push_back(sample);
    }
    elementIndex %= stride;
  }

  void pushBackZeros(int zerosCount) {
    for (; elementIndex < zerosCount; elementIndex += stride) {
      stridedElements.pop_front();
      stridedElements.push_back(0.f);
    }
    elementIndex %= stride;
  }

private:
  std::deque<float> stridedElements;
  int elementIndex{0};
  int stride{1};
};
}  // namespace ws::detail
