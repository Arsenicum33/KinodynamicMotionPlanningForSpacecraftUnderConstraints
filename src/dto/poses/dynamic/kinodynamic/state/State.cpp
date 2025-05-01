//
// Created by arseniy on 20.3.25.
//

#include "State.h"

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
