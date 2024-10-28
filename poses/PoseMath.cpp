//
// Created by arseniy on 13.10.24.
//

#include "PoseMath.h"

#include <iostream>
#include <ostream>
#include <cmath>



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

std::vector<Pose> PoseMath::interpolatePoses(const Pose &start, const Pose &end, double interpolationThreshold, double rotationThreshold)
{
    double dx = end.translation[0] - start.translation[0];
    double dy = end.translation[1] - start.translation[1];
    double dz = end.translation[2] - start.translation[2];
    double distance = sqrt(dx * dx + dy * dy + dz * dz);
    int translationSteps = static_cast<int>(distance / interpolationThreshold);


    Eigen::Quaterniond rotationStart = PoseMath::rotationMatrixToQuaternion(start.rotation);
    Eigen::Quaterniond rotationEnd = PoseMath::rotationMatrixToQuaternion(end.rotation);
    double angle = 2 * acos(std::abs(rotationStart.dot(rotationEnd))); // Angle between quaternions
    int rotationSteps = static_cast<int>(angle / rotationThreshold);

    int maxSteps = std::max(translationSteps, rotationSteps);

    std::vector<Pose> poses { start };

    for (int i = 1; i <= maxSteps; i++)
    {
        double t = static_cast<double>(i) / static_cast<double>(maxSteps);
        std::array<double, 3> newTranslation =
        {
            start.translation[0] + t * dx,
            start.translation[1] + t * dy,
            start.translation[2] + t * dz
        };

        Eigen::Quaterniond newRotation = rotationStart.slerp(t, rotationEnd);

        Pose p(newTranslation, newRotation);
        poses.push_back(p);
    }
    poses.push_back(end);
    return poses;
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
    Eigen::Quaterniond quaternion(rotation_matrix);
    return quaternion;
}

Pose PoseMath::getPoseWithinStepSize(const Pose &from, const Pose &to, double stepSize, const std::shared_ptr<IDistanceMetric>& distanceMetric)
{
    double distance = distanceMetric->getDistance(from, to);
    if (distance <= stepSize)
    {
        return to;
    }

    double scale = stepSize / distance;

    std::array<double, 3> newTranslation;
    for (int i = 0; i < 3; ++i)
    {
        newTranslation[i] = from.translation[i] + scale * (to.translation[i] - from.translation[i]);
    }

    Eigen::Quaterniond rotationFrom = rotationMatrixToQuaternion(from.rotation);
    Eigen::Quaterniond rotationTo = rotationMatrixToQuaternion(to.rotation);
    Eigen::Quaterniond newRotation = rotationFrom.slerp(scale, rotationTo);
    Pose newPose(newTranslation, newRotation);
    double newDistance = distanceMetric->getDistance(from, newPose);
    return newPose;
}
