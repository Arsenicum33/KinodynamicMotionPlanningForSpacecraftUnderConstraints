//
// Created by arseniy on 13.10.24.
//

#include "PoseMath.h"

#include <iostream>
#include <ostream>
#include <cmath>
#include <spdlog/spdlog.h>


#define ALMOST_ZERO 1e-6

std::array<double, 3> PoseMath::rotationMatrixToEuler(const double R[3][3])
{
    double roll, pitch, yaw;
    pitch = atan2(-R[2][0], sqrt(R[0][0] * R[0][0] + R[1][0] * R[1][0]));

    if (std::abs(std::abs(pitch) - M_PI_2) > ALMOST_ZERO)
    {
        yaw = atan2(R[1][0], R[0][0]);
        roll = atan2(R[2][1], R[2][2]);
    }
    else
    {
        spdlog::warn("Gimbal lock");
        roll = 0;
        yaw = atan2(R[0][1], R[1][1]);
    }
    return std::array<double, 3>{roll, pitch, yaw};
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
        {cp * cy, cy * sp * sr - sy * cr, cy * sp * cr + sy * sr},
        {sy * cp, sy * sp * sr + cy * cr, sy * sp * cr - cy * sr},
        {-sp, cp * sr, cp * cr}
    }};

    return R;
}


std::array<std::array<double, 3>, 3> PoseMath::getIdentityRotationMatrix()
{
    std::array<std::array<double, 3>, 3> matrix = {{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}}};
    return matrix;
}

Eigen::Quaterniond PoseMath::rotationMatrixToQuaternion(const double rotation[3][3])
{
    Eigen::Matrix3d rotation_matrix;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            rotation_matrix(i, j) = rotation[i][j];
        }
    }
    if (!rotation_matrix.isUnitary(1e-6)) {
        throw std::runtime_error("Invalid rotation matrix: not unitary");
    }
    if (std::abs(rotation_matrix.determinant() - 1.0) > 1e-6) {
        throw std::runtime_error("Invalid rotation matrix: determinant != 1");
    }
    Eigen::Quaterniond quaternion(rotation_matrix);
    quaternion.normalize();
    if (quaternion.w() < 0) {
        quaternion = Eigen::Quaterniond(-quaternion.w(), -quaternion.x(), -quaternion.y(), -quaternion.z());
    }
    return quaternion;
}
