//
// Created by arseniy on 20.3.25.
//

#ifndef STATE_H
#define STATE_H
#include <dto/poses/dynamic/keyframe/Keyframe.h>


class State : public Keyframe
{
public:
    State()
        : Keyframe(), // translation = {0,0,0}, rotation = identity, time = -1
          velocity{0.0, 0.0, 0.0},
          acceleration{0.0, 0.0, 0.0},
          angularVelocity{0.0, 0.0, 0.0},
          angularAcceleration{0.0, 0.0, 0.0} {}

    State(std::array<double, 3> trans, Eigen::Quaterniond rot, double t,
          std::array<double, 3> vel, std::array<double, 3> acc,
          std::array<double, 3> angVel, std::array<double, 3> angAcc)
        : Keyframe(trans, rot, t),
          velocity(vel),
          acceleration(acc),
          angularVelocity(angVel),
          angularAcceleration(angAcc) {}

    State(std::array<double, 3> trans, Eigen::Quaterniond rot, double t,
          std::array<double, 3> vel, std::array<double, 3> angVel)
        : Keyframe(trans, rot, t),
          velocity(vel),
          acceleration{0.0, 0.0, 0.0},
          angularVelocity(angVel),
          angularAcceleration{0.0, 0.0, 0.0} {}

    std::array<double, 3> velocity;
    std::array<double, 3> acceleration;
    std::array<double, 3> angularVelocity;
    std::array<double, 3> angularAcceleration;
};



#endif //STATE_H
