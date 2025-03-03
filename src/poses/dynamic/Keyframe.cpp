//
// Created by arseniy on 2.1.25.
//

#include "Keyframe.h"

std::string Keyframe::toString() const
{
    return Pose::toString() + "Time: " + std::to_string(time);
}
