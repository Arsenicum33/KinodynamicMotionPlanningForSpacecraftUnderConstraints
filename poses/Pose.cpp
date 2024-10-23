//
// Created by arseniy on 13.10.24.
//
#include "Pose.h"

#include "PoseMath.h"

std::array<double, 6> Pose::flatten() const
{
    auto eulersAngles = PoseMath::rotationMatrixToEuler(rotation);
    std::array<double, 6> configuration = {translation[0], translation[1], translation[2],
    eulersAngles[0], eulersAngles[1], eulersAngles[2]};
    return configuration;
}
