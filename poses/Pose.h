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
    Pose(const std::array<double, 3>& trans, const double rot[3][3]):
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

    Pose(const std::array<double, 3>& trans, std::array<std::array<double,3>,3> rot):
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

    Pose(const std::array<double, 3>& trans):translation(trans)
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

    std::array<double, 6> flatten() const;

    std::array<double, 3> translation;
    double rotation[3][3];
};




#endif
