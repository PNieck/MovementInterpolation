#pragma once

#include <vector>
#include <queue>

#include "../views/visualization/frame.hpp"

#include "../model/positionInterpolator.hpp"
#include "../model/quaternionInterpolator.hpp"
#include "../model/eulerAnglesInterpolator.hpp"


class FramesCapturer {
public:
    FramesCapturer(PositionInterpolator& pos, QuaternionInterpolator& quat, EulerAnglesInterpolator& eul):
        positionInterpolator(pos),
        quaternionInterpolator(quat),
        eulerAnglesInterpolator(eul) {}

    void SetNumberOfFramesToCapture(int numberOfFrames);

    [[nodiscard]]
    int GetNumberOfFrames() const
        { return framesToCapture; }

    void Update(float t, QuaternionInterpolator::Types interpolationType);

    [[nodiscard]]
    const std::vector<Frame>& GetQuaternionInterpolationFrames() const
        { return quaternionFrames; }

    [[nodiscard]]
    const std::vector<Frame>& GetEulerAnglesInterpolationFrames() const
        { return eulerFrames; }

    void Clear();

private:
    PositionInterpolator& positionInterpolator;
    QuaternionInterpolator& quaternionInterpolator;
    EulerAnglesInterpolator& eulerAnglesInterpolator;

    std::vector<Frame> quaternionFrames;
    std::vector<Frame> eulerFrames;

    int framesToCapture = 0;
    std::queue<float> remainingTimesToCapture;
};
