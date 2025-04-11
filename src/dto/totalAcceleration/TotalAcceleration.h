//
// Created by arseniy on 11.4.25.
//

#ifndef TOTALACCELERATION_H
#define TOTALACCELERATION_H
#include <array>
#include <utils/PhysicsUtils.h>

class TotalAcceleration
{
public:
    TotalAcceleration() : linearAcceleration{0, 0, 0}, angularAcceleration{0, 0, 0} {}
    TotalAcceleration(std::array<double, 3>  linearAcceleration, std::array<double, 3>  angularAcceleration) :
        linearAcceleration(linearAcceleration), angularAcceleration(angularAcceleration) {}

    const std::array<double, 3>& getLinearAcceleration() const { return linearAcceleration; }
    const std::array<double, 3>& getAngularAcceleration() const { return angularAcceleration; }


    TotalAcceleration operator+(const TotalAcceleration& other) const {
        using namespace PhysicsUtils;
        return TotalAcceleration(linearAcceleration + other.linearAcceleration, angularAcceleration + other.angularAcceleration);
    }
    TotalAcceleration &operator+=(const TotalAcceleration & other)
    {
        using namespace PhysicsUtils;
        linearAcceleration+=other.linearAcceleration;
        angularAcceleration+=other.angularAcceleration;
        return *this;
    }


private:
    std::array<double, 3> linearAcceleration;  // (km / s^2)
    std::array<double, 3> angularAcceleration; // (rad / s^2)
};


#endif //TOTALACCELERATION_H
