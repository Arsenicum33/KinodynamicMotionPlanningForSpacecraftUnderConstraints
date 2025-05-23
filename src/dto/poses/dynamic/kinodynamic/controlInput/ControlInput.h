// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef CONTROLINPUT_H
#define CONTROLINPUT_H
#include <array>


class ControlInput
{
public:
    ControlInput()
        : thrust(0.0),
          torque{0.0, 0.0, 0.0} {}

    ControlInput(double thrust, std::array<double, 3> torque)
        : thrust(thrust),
          torque(torque) {}

    double getThrust() const { return thrust; }
    std::array<double, 3> getTorque() const { return torque; }

private:
    double thrust;
    std::array<double, 3> torque;
};



#endif //CONTROLINPUT_H
