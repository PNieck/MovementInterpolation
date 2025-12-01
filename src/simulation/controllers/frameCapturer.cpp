#include <simulation/controllers/framesCapturer.hpp>


void FramesCapturer::SetNumberOfFramesToCapture(const int numberOfFrames) {
    framesToCapture = numberOfFrames;

    while (!remainingTimesToCapture.empty())
        remainingTimesToCapture.pop();

    for (int i=1; i <= framesToCapture; i++) {
        remainingTimesToCapture.push(static_cast<float>(i) / static_cast<float>(numberOfFrames + 1));
    }

    quaternionFrames.reserve(numberOfFrames);
    eulerFrames.reserve(numberOfFrames);
}


void FramesCapturer::Update(const float t, QuaternionInterpolator::Types interpolationType) {
    while (!remainingTimesToCapture.empty() && remainingTimesToCapture.front() < t) {
        const float interpolationT = remainingTimesToCapture.front();
        remainingTimesToCapture.pop();

        auto pos = positionInterpolator.Interpolate(interpolationT);
        quaternionFrames.emplace_back(pos, quaternionInterpolator.Interpolate(interpolationT, interpolationType));
        eulerFrames.emplace_back(pos, eulerAnglesInterpolator.Interpolate(interpolationT));
    }
}


void FramesCapturer::Clear() {
    quaternionFrames.clear();
    eulerFrames.clear();

    SetNumberOfFramesToCapture(framesToCapture);
}
