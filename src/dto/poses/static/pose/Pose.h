// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef POSE_H
#define POSE_H
#include <array>

#include "eigen3/Eigen/Eigen"

class Pose
{
public:
    virtual ~Pose() = default;

    Pose();
    Pose(std::array<double, 3> trans, double rot[3][3]);

    Pose(std::array<double, 3> trans, std::array<std::array<double,3>,3> rot);

    Pose(std::array<double, 3> trans, std::array<double, 3> rot);

    Pose(std::array<double, 3> trans, Eigen::Quaterniond rot);

    Pose(std::array<double, 3> trans);

    virtual std::vector<double> flatten() const;

    virtual std::vector<double> flattenNoRot() const;

    virtual std::string toString() const;


    Pose operator+(const Pose &other) const; //only for operations with derivative

    Pose operator*(double factor) const; //only for operations with derivative

    virtual void validate(const std::string& where) const;

    std::array<double, 3> translation;
    Eigen::Quaterniond rotation;
};




#endif
