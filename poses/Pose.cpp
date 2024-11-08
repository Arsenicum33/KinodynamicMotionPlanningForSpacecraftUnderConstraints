//
// Created by arseniy on 13.10.24.
//
#include "Pose.h"

#include "PoseMath.h"

Pose::Pose(const std::array<double, 3> &trans, const double rot[3][3]):
    translation(trans)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            rotation[i][j] = rot[i][j];
        }
    }
}

Pose::Pose(const std::array<double, 3> &trans, std::array<std::array<double, 3>, 3> rot):
    translation(trans)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            rotation[i][j] = rot[i][j];
        }
    }
}

Pose::Pose(const std::array<double, 3> &trans, Eigen::Quaterniond rot):
    translation(trans)
{
    Eigen::Matrix3d eigenMatrix = rot.toRotationMatrix();
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            rotation[i][j] = eigenMatrix(i, j);
        }
    }
}

Pose::Pose(const std::array<double, 3> &trans):translation(trans)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            rotation[i][j] = 0.0;
        }
    }
    rotation[0][0] = 1.0;
    rotation[1][1] = 1.0;
    rotation[2][2] = 1.0;
}

std::vector<double> Pose::flatten() const
{
    auto eulersAngles = PoseMath::rotationMatrixToEuler(rotation);
    std::vector<double> configuration = {translation[0], translation[1], translation[2],
    eulersAngles[0], eulersAngles[1], eulersAngles[2]};
    return configuration;
}
