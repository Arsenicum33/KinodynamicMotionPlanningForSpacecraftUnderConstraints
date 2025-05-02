//
// Created by arseniy on 13.10.24.
//

#ifndef POSEMATH_H
#define POSEMATH_H
#include <array>
#include <vector>
#include "eigen3/Eigen/Eigen"
#include <memory>

#define ROTATION_THRESHOLD 0.1
struct RotationMatrix {
    double data[3][3];
};

class PoseMath
{
public:
    PoseMath() = delete;
    static std::array<double, 3> rotationMatrixToEuler(const double rotationMatrix[3][3]);
    static std::array<std::array<double, 3>, 3> eulerToRotationMatrix(const std::array<double, 3>& euler);
    static std::array<std::array<double, 3>, 3>  getIdentityRotationMatrix();

    static Eigen::Quaterniond eulerToQuaternion(const std::array<double, 3>& euler);
    static Eigen::Quaterniond rotationMatrixToQuaternion(const double rotation[3][3]);
    static Eigen::Quaterniond rotationMatrixToQuaternion(const std::array<std::array<double, 3>, 3>& rotation);

    static RotationMatrix quaternionToRotationMatrix(const Eigen::Quaterniond& quaternion);
};



#endif //POSEMATH_H
