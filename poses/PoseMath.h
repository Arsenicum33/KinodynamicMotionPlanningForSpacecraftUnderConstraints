//
// Created by arseniy on 13.10.24.
//

#ifndef POSEMATH_H
#define POSEMATH_H
#include <array>
#include <vector>
#include "eigen3/Eigen/Eigen"
#include "Pose.h"
#include "../distanceMeasurement /IDistanceMetric.h"
#include <memory>

#define ROTATION_THRESHOLD 0.1
class PoseMath
{
public:
    PoseMath() = delete;
    static std::array<double, 3> rotationMatrixToEuler(const double rotationMatrix[3][3]);
    static std::array<std::array<double, 3>, 3> eulerToRotationMatrix(const std::array<double, 3>& euler);
    static std::vector<Pose> interpolatePoses(const Pose &start, const Pose &end, double interpolationThreshold, double rotationThreshold);
    static std::array<std::array<double, 3>, 3>  getIdentityRotationMatrix();
    static Eigen::Quaterniond rotationMatrixToQuaternion(const double rotation[3][3]);
    static Pose getPoseWithinStepSize(const Pose &from, const Pose &to, double stepSize, const std::shared_ptr<IDistanceMetric>& distanceMetric);
};



#endif //POSEMATH_H
