//
// Created by arseniy on 20.3.25.
//

#ifndef CONTROLINPUT_H
#define CONTROLINPUT_H
#include <array>


class ControlInput
{
public:
    ControlInput()
        : linearAcceleration(0.0),
          angularAcceleration{0.0, 0.0, 0.0} {}

    ControlInput(double linAcc, std::array<double, 3> angAcc)
        : linearAcceleration(linAcc),
          angularAcceleration(angAcc) {}

    double getLinearAcceleration() const { return linearAcceleration; }
    std::array<double, 3> getAngularAcceleration() const { return angularAcceleration; }

private:
    double linearAcceleration;
    std::array<double, 3> angularAcceleration;
};



#endif //CONTROLINPUT_H
