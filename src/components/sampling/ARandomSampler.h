//
// Created by arseniy on 18.3.25.
//

#ifndef ARANDOMSAMPLER_H
#define ARANDOMSAMPLER_H
#include <random>
#include <poses/static/PoseMath.h>

#include "ISampler.h"

template <typename PositionType, typename TargetType>
class ARandomSampler : public ISampler<PositionType, TargetType>
{
protected:
    Pose sampleRandomPose();

    ARandomSampler(ConfigurationSpaceBoundaries boundaries) :
        dis_x(boundaries.xMin, boundaries.xMax),
        dis_y(boundaries.yMin, boundaries.yMax),
        dis_z(boundaries.zMin, boundaries.zMax),
        dis_yaw(boundaries.yaw_min, boundaries.yaw_max),
        dis_pitch(boundaries.pitch_min, boundaries.pitch_max),
        dis_roll(boundaries.roll_min, boundaries.roll_max) {}

    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dis_x;
    std::uniform_real_distribution<double> dis_y;
    std::uniform_real_distribution<double> dis_z;
    std::uniform_real_distribution<double> dis_yaw;
    std::uniform_real_distribution<double> dis_pitch;
    std::uniform_real_distribution<double> dis_roll;



};

template<typename PositionType, typename TargetType>
Pose ARandomSampler<PositionType, TargetType>::sampleRandomPose()
{
    std::array<double, 3> translation = {dis_x(gen), dis_y(gen), dis_z(gen)};
    std::array<double, 3> eulerAngles = {dis_yaw(gen), dis_pitch(gen), dis_roll(gen)};
    std::array<std::array<double, 3>, 3> rotation_matrix = PoseMath::eulerToRotationMatrix(eulerAngles);
    Pose pose(translation, rotation_matrix);
    return pose;
}

#endif //ARANDOMSAMPLER_H
