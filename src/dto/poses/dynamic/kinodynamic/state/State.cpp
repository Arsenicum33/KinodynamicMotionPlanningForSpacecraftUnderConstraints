// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "State.h"

#include <spdlog/spdlog.h>
#include <utils/PhysicsUtils.h>

State State::operator+(const State &other) const
{
    using namespace PhysicsUtils;
    Keyframe keyframeSum = Keyframe::operator+(other);
    std::array<double,3> velocitySum = velocity + other.velocity;
    std::array<double,3> angularVelocitySum = angularVelocity + other.angularVelocity;
    return State(keyframeSum, velocitySum, angularVelocitySum);
}

State State::operator*(double factor) const
{
    using namespace PhysicsUtils;
    Keyframe keyframeMult = Keyframe::operator*(factor);
    std::array<double,3> velocityMult= velocity * factor;
    std::array<double,3> angularVelocityMult = angularVelocity * factor;
    return State(keyframeMult, velocityMult, angularVelocityMult);
}

void State::validate(const std::string& where) const
{
    for (int i = 0; i < 3; ++i) {
        if (!std::isfinite(velocity[i])) {
            spdlog::debug("State velocity invalid in {}", where);
            break;
        }
    }

    for (int i = 0; i < 3; ++i) {
        if (!std::isfinite(angularVelocity[i])) {
            spdlog::debug("State angular velocity invalid in {}", where);
            break;
        }
    }
}

