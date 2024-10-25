//
// Created by arseniy on 13.10.24.
//

#include "PoseMath.h"

#include <iostream>
#include <ostream>
#include <cmath>
#include <eigen3/Eigen/Geometry>
#define ALMOST_ZERO 1e-6

std::array<double, 3> PoseMath::rotationMatrixToEuler(const double R[3][3])
{
    double alpha, beta, gamma;
    beta = atan2(-R[2][0], sqrt(R[0][0] * R[0][0] + R[1][0] * R[1][0]));

    if (std::abs(beta - M_PI_2) > ALMOST_ZERO)
    {
        alpha = atan2(R[1][0], R[0][0]);
        gamma = atan2(R[2][1], R[2][2]);
    }
    else
    {
        std::cerr << "Gimbal lock" << std::endl;
        alpha = 0;
        gamma = atan2(R[0][1], R[1][1]);
    }
    return std::array<double, 3>{alpha, beta, gamma};
}

std::array<std::array<double, 3>, 3> PoseMath::eulerToRotationMatrix(const std::array<double, 3> &euler)
{
    const double roll = euler[0];
    const double pitch = euler[1];
    const double yaw = euler[2];

    const double cr = cos(roll);
    const double sr = sin(roll);
    const double cp = cos(pitch);
    const double sp = sin(pitch);
    const double cy = cos(yaw);
    const double sy = sin(yaw);

    std::array<std::array<double, 3>, 3> R = {{
        {cp * cy, cp * sy, -sp},
        {sr * sp * cy - cr * sy, sr * sp * sy + cr * cy, sr * cp},
        {cr * sp * cy + sr * sy, cr * sp * sy - sr * cy, cr * cp}
    }};

    return R;
}

std::vector<Pose> PoseMath::interpolatePoses(const Pose &start, const Pose &end, double interpolationThreshold)
{
    double dx = end.translation[0] - start.translation[0];
    double dy = end.translation[1] - start.translation[1];
    double dz = end.translation[2] - start.translation[2];
    double distance = sqrt(dx * dx + dy * dy + dz * dz);
    int translationSteps = distance / interpolationThreshold;
    std::vector<Pose> poses { start };
    for (int i = 1; i <= translationSteps; i++)
    {
        std::array<double, 3> newTranslation ={
            start.translation[0] + (end.translation[0] - start.translation[0])*(static_cast<double>(i) / static_cast<double>(translationSteps+1)) ,
            start.translation[1] + (end.translation[1] - start.translation[1])*(static_cast<double>(i) / static_cast<double>(translationSteps+1)) ,
            start.translation[2] + (end.translation[2] - start.translation[2])*(static_cast<double>(i) / static_cast<double>(translationSteps+1))
        };
        Pose p(newTranslation, start.rotation);
        poses.push_back(p);
    }
    poses.push_back(end);
    //TODO: Account for rotations!
    return poses;
}