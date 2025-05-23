// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef STATE_H
#define STATE_H
#include <dto/poses/dynamic/keyframe/Keyframe.h>


class State : public Keyframe
{
public:
    State()
        : Keyframe(), // translation = {0,0,0}, rotation = identity, time = -1
          velocity{0.0, 0.0, 0.0},
          angularVelocity{0.0, 0.0, 0.0}
    {
    }

    State(std::array<double, 3> trans, Eigen::Quaterniond rot, double t,
          std::array<double, 3> vel,
          std::array<double, 3> angVel)
        : Keyframe(trans, rot, t),
          velocity(vel),
          angularVelocity(angVel)
    {
    }

    State(std::array<double, 3> trans, std::array<std::array<double, 3>, 3> rot, double t,
          std::array<double, 3> vel,
          std::array<double, 3> angVel)
        : Keyframe(trans, rot, t),
          velocity(vel),
          angularVelocity(angVel)
    {
    }

    State(Keyframe keyframe, std::array<double, 3> vel, std::array<double, 3> angVel)
        : Keyframe(keyframe), velocity(vel), angularVelocity(angVel)
    {
    }

    State operator+(const State &other) const; //only for operations with derivative

    State operator*(double factor) const; //only for operations with derivative

    void validate(const std::string& where) const override;

    std::array<double, 3> velocity;
    std::array<double, 3> angularVelocity;
};


#endif //STATE_H
