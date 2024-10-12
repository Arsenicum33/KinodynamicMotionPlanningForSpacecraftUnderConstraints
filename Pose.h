//
// Created by arseniy on 12.10.24.
//

#ifndef POSE_H
#define POSE_H
#include <array>


class Pose
{
    public:
    Pose();
    Pose(const std::array<double, 3>& trans, const std::array<std::array<double, 3>, 3>& rot):
        translation(trans), rotation(rot) {}
    const std::array<double, 3> translation;
    const std::array<std::array<double, 3>, 3> rotation;
};



#endif
